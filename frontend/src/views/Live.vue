<template>
    <v-container class="container" fluid align="center" background-color="surface">
     <v-row class="row row1" max-width="1200px" justify="center" align="center">
         <v-col class="col col1" cols="8" align="center">
             <figure class="highcharts-figure custom-chart">
                 <div id="container" class="custom-chart"></div>
             </figure>
         </v-col>
         <v-col class="col col2" cols="4" align="center"> 
             <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="primaryContainer" subtitle="Temperature">
                 <v-card-item class="custom-card-text">
                     <span class="text-p3 text-onPrimaryContainer"  style="font-size: 35px;">{{ temperature }}</span>
                 </v-card-item>
                 <v-card-item>
                     <v-btn @click="toggleTemperatureUnit" class="custom-btn">{{ tempUnit}}</v-btn>
                 </v-card-item>
             </VCard>  
         </v-col>
       </v-row>
       <v-row class="row row2" max-width="1200px" justify="center" align="center">
         <v-col class="col col1" cols="8" align="center">
             <figure class="highcharts-figure custom-chart">
                 <div id="container1" class="custom-chart"></div>
             </figure>
         </v-col>
         <v-col class="col col2" cols="4" align="center"> 
             <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="tertiaryContainer" subtitle="HeatIndex (Feels Like)">
                 <v-card-item class="custom-card-text">
                     <span class="text-p3 text-onTertiaryContainer"  style="font-size: 35px;">{{ heatindex }}</span>
                 </v-card-item>
                 <v-card-item>
                     <v-btn @click="toggleHeatIndexUnit" class="custom-btn">{{ heatIndexUnit }}</v-btn>
                 </v-card-item>
             </VCard> 
         </v-col>
       </v-row>
       <v-row class="row row3" max-width="1200px" justify="center" align="center">
         <v-col class="col col1" cols="8" align="center"> 
             <figure class="highcharts-figure custom-chart">
                 <div id="container2" class="custom-chart"></div>
             </figure>
         </v-col>
         <v-col class="col col2" cols="4" align="center"> 
             <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="secondaryContainer" subtitle="Humidity">
                 <v-card-item class="custom-card-text">
                     <span class="text-p3 text-onSecondaryContainer"  style="font-size: 35px;">{{ humidity }}</span>
                 </v-card-item>
                 <v-card-item></v-card-item>
             </VCard> 
         </v-col>
       </v-row>
       <v-row class="row row4" max-width="1200px" justify="center" align="center">
             <v-col class="col col1" cols="8" align="center"> 
                 <figure class="highcharts-figure custom-chart">
                     <div id="container3" class="custom-chart"></div>
                 </figure>
             </v-col>
             <v-col class="col col2" cols="4" align="center"> 
                 <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="red" subtitle="Pressure">
                         <v-card-item class="custom-card-text">
                             <span class="text-p3 text-onSecondaryContainer" style="font-size: 35px;">{{ pressure }}</span>
                         </v-card-item>
                         <v-card-item>    
                             <v-btn @click="togglePressureUnit" class="custom-btn">{{ pressureUnit}}</v-btn>
                         </v-card-item>
                 </VCard> 
             </v-col>
       </v-row>
       <v-row class="row row5" max-width="1200px" justify="center" align="center">
             <v-col class="col col1" cols="8" align="center"> 
                 <figure class="highcharts-figure custom-chart">
                     <div id="container4" class="custom-chart"></div>
                 </figure>
             </v-col>
             <v-col class="col col2" cols="4" align="center"> 
                 <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="blue" subtitle="Altitude">
                         <v-card-item class="custom-card-text">
                             <span class="text-p3 text-onSecondaryContainer"  style="font-size: 35px;">{{ altitude }}</span>
                         </v-card-item>
                         <v-card-item>
                             <v-btn @click="toggleAltitudeUnit" class="custom-btn">{{ altitudeUnit}}</v-btn>
                         </v-card-item>
                 </VCard> 
             </v-col>
       </v-row>
 
      <v-row class="row row6" max-width="1200px" justify="center" align="center">
         <v-col class="col col1" cols="8" align="center"> 
             <figure class="highcharts-figure custom-chart">
                 <div id="container5" class="custom-chart"></div>
             </figure>
         </v-col>
         <v-col class="col col2" cols="4" align="center"> 
             <VCard class="custom-card" margin-bottom="5px" max-width="500px" color="green" subtitle="Soil Moisture">
                 <v-card-item class="custom-card-text">
                     <span class="text-p3 text-onSecondaryContainer" style="font-size: 35px;">{{ soil }}</span>
                 </v-card-item>
                 <v-card-item></v-card-item>
             </VCard> 
         </v-col>
       </v-row>
    </v-container>
 </template>

<script setup>
/** JAVASCRIPT HERE */

// IMPORTS
import { ref,reactive,watch ,onMounted,onBeforeUnmount,computed } from "vue";  
import { useRoute ,useRouter } from "vue-router";

// Highcharts, Load the exporting module and Initialize exporting module.
import Highcharts from 'highcharts';
import more from 'highcharts/highcharts-more';
import Exporting from 'highcharts/modules/exporting';
import { useMqttStore } from '@/store/mqttStore'; // Import Mqtt Store
import { storeToRefs } from "pinia";
import { useAppStore } from "@/store/appStore";

Exporting(Highcharts);
more(Highcharts);
 
// VARIABLES
const router      = useRouter();
const route       = useRoute();  
const tempHiChart = ref(null); // Chart object
const humHiChart = ref(null);
const heatChart= ref(null);
const pressChart = ref(null);
const altChart = ref(null);
const praltChart = ref(null);
const soilChart = ref(null);
const points = ref(10); // Specify the quantity of points to be shown on the live graph simultaneously.
const shift = ref(false); // Delete a point from the left side and append a new point to the right side of the graph.
const AppStore = useAppStore();
const Mqtt = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
const tempUnit = ref('°C'); 
const heatIndexUnit = ref('°C'); 
const pressureUnit = ref('kPa');
const altitudeUnit = ref('m'); 

// FUNCTIONS
onMounted(()=>{
    // THIS FUNCTION IS CALLED AFTER THIS COMPONENT HAS BEEN MOUNTED
    CreateCharts();
    Mqtt.connect(); // Connect to Broker located on the backend
    setTimeout( ()=>{
        // Subscribe to each topic
        Mqtt.subscribe("620155784");
        Mqtt.subscribe("620155784_sub");
        Mqtt.subscribe("620155784_pub");
        },
    3000);

    /*setInterval(function(){
        window.location.reload();
    },30000);*/
    
})

onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});


const CreateCharts = async () => {
// TEMPERATURE CHART
    tempHiChart.value = Highcharts.chart('container', {
        chart: { zoomType: 'x' },
        title: { text: 'Air Temperature Analysis', align: 'left' },
        yAxis: {
            title: { text: 'Air Temperature' , style:{color:'#000000'}},
            labels: { format: '{value} °C' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [
            {
                name: 'Temperature',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
         ],
    });

    heatChart.value = Highcharts.chart('container1', {
        chart: { zoomType: 'x' },
        title: { text: 'Heat Index Analysis', align: 'left' },
        yAxis: {
            title: { text: 'HeatIndex' , style:{color:'#000000'}},
            labels: { format: '{value} °C' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [{
                name: 'Heat Index',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1]
         } ],
    });

    humHiChart.value = Highcharts.chart('container2', {
        chart: { zoomType: 'x' },
        title: { text: 'Humidity Analysis', align: 'left' },
        yAxis: {
            title: { text: 'Humidity' , style:{color:'#000000'}},
            labels: { format: '{value} %' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [
            {
                name: 'Humidity',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
         ]
    });

    altChart.value = Highcharts.chart('container4', {
        chart: { zoomType: 'x' },
        title: { text: 'Altitude Analysis', align: 'left' },
        yAxis: {
            title: { text: 'Altitude' , style:{color:'#000000'}},
            labels: { format: '{value} m' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [
            {
                name: 'Altitude',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
         ]
    });

    pressChart.value = Highcharts.chart('container3', {
        chart: { zoomType: 'x' },
        title: { text: 'Pressure Analysis', align: 'left' },
        yAxis: {
            title: { text: 'Pressure' , style:{color:'#000000'}},
            labels: { format: '{value} kPa' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [
            {
                name: 'Pressure',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
         ]
    });
    

    

    soilChart.value = Highcharts.chart('container5', {
        chart: { zoomType: 'x' },
        title: { text: 'Soil Moisture Analysis', align: 'left' },
        yAxis: {
            title: { text: 'Soil moisture' , style:{color:'#000000'}},
            labels: { format: '{value} %' }
        },
        xAxis: {
            type: 'datetime',
            title: { text: 'Time', style:{color:'#000000'} },
        },
        tooltip: { shared:true, },
        series: [
            {
                name: 'Soil moisture',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
         ]
    });
}

// WATCHERS
watch(payload,(data)=> {
    if(points.value > 0){ points.value -- ; }
    else{ shift.value = true; }
    
    tempHiChart.value.series[0].addPoint({y:parseFloat(convertTemperature(data.temperature).toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    heatChart.value.series[0].addPoint({y:parseFloat(convertHeatIndex(data.heatindex).toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    humHiChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    pressChart.value.series[0].addPoint({y:parseFloat(convertPressure(data.pressure).toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    altChart.value.series[0].addPoint({y:parseFloat(convertAltitude(data.altitude).toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    soilChart.value.series[0].addPoint({y:parseFloat(data.soilMoisture.toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
})

// COMPUTED PROPERTIES
const toggleTemperatureUnit = () => {
    if (tempUnit.value === '°C') {
        tempUnit.value = '°F';
    } else {
        tempUnit.value = '°C';
    }
    updateTemperatureChart();
};

const convertTemperature = (temp) => {
    if (tempUnit.value === '°F') {
        return (temp * 9/5) + 32; // Convert Celsius to Fahrenheit
    } 
    else {
        return temp; // Temperature is already in Celsius
    }
};

const updateTemperatureChart = () => {
    const temperatureData = tempHiChart.value.series[0].data.map(point => {
        return [point.x, convertTemperature(point.y)];
    });

    tempHiChart.value.update({
        yAxis: {
            title: { text: `Temperature (${tempUnit.value})`, style:{color:'#000000'} },
            labels: { format: `{value} ${tempUnit.value}` }
        },
        series: [{
            data: temperatureData
        }]
    });
};

const temperature = computed(() => {
    if (!!payload.value) {
        const convertedTemp = convertTemperature(payload.value.temperature);
        return `${convertedTemp.toFixed(2)} ${tempUnit.value}`;
    }
});

const humidity = computed(()=>{
    if(!!payload.value){
        return `${payload.value.humidity.toFixed(2)} %`;
    }
});

const toggleHeatIndexUnit = () => {
    if (heatIndexUnit.value === '°C') {
        heatIndexUnit.value = '°F';
    } else {
        heatIndexUnit.value = '°C';
    }
    updateHeatIndexChart();
};

const updateHeatIndexChart = () => {
    const heatIndexData = heatChart.value.series[0].data.map(point => {
        return [point.x, convertHeatIndex(point.y)];
    });

    heatChart.value.update({
        yAxis: {
            title: { text: `Heat Index (${heatIndexUnit.value})`, style:{color:'#000000'} },
            labels: { format: `{value} ${heatIndexUnit.value}` }
        },
        series: [{
            data: heatIndexData
        }]
    });
};

const convertHeatIndex = (heatIndex) => {
    if (heatIndexUnit.value === '°F') {
        return (heatIndex * 9/5) + 32; // Convert Celsius to Fahrenheit
    } else {
        return heatIndex; // Heat index is already in Celsius
    }
};

const heatindex = computed(() => {
    if (!!payload.value) {
        const convertedHeatIndex = convertHeatIndex(payload.value.heatindex);
        return `${convertedHeatIndex.toFixed(2)} ${heatIndexUnit.value}`;
    }
});

const togglePressureUnit = () => {
    switch (pressureUnit.value) {
        case 'kPa':
            pressureUnit.value = 'hPa';
            break;
        case 'hPa':
            pressureUnit.value = 'mmHg';
            break;
        case 'mmHg':
            pressureUnit.value = 'kPa';
            break;
    }
    updatePressureChart();
};

const convertPressure = (pressure) => {
    switch (pressureUnit.value) {
        case 'hPa':
            return pressure * 10; // Convert kPa to hPa
        case 'mmHg':
            return pressure * 7.50062; // Convert kPa to mmHg
        case 'kPa':
        default:
            return pressure; // Pressure is already in kPa
    }
};

const updatePressureChart = () => {
    const pressureData = pressChart.value.series[0].data.map(point => {
        return [point.x, convertPressure(point.y)];
    });

    pressChart.value.update({
        yAxis: {
            title: { text: `Pressure (${pressureUnit.value})`, style:{color:'#000000'} },
            labels: { format: `{value} ${pressureUnit.value}` }
        },
        series: [{
            data: pressureData
        }]
    });
};

const pressure = computed(() => {
    if (!!payload.value) {
        const convertedPressure = convertPressure(payload.value.pressure);
        return `${convertedPressure.toFixed(2)} ${pressureUnit.value}`;
    }
});


const toggleAltitudeUnit = () => {
    switch (altitudeUnit.value) {
        case 'm':
            altitudeUnit.value = 'ft';
            break;
        case 'ft':
            altitudeUnit.value = 'km';
            break;
        case 'km':
            altitudeUnit.value = 'm';
            break;
    }
    updateAltitudeChart();
};

const convertAltitude = (altitude) => {
    switch (altitudeUnit.value) {
        case 'ft':
            return altitude * 3.28084; // Convert meters to feet
        case 'km':
            return altitude / 1000; // Convert meters to kilometers
        case 'm':
            return altitude; // Altitude is already in meters
    }
};

const updateAltitudeChart = () => {
    const altitudeData = altChart.value.series[0].data.map(point => {
        return [point.x, convertAltitude(point.y)];
    });

    altChart.value.update({
        yAxis: {
            title: { text: `Altitude (${altitudeUnit.value})`, style:{color:'#000000'} },
            labels: { format: `{value} ${altitudeUnit.value}` }
        },
        series: [{
            data: altitudeData
        }]
    });
};

const altitude = computed(() => {
    if (!!payload.value) {
        const convertedAltitude = convertAltitude(payload.value.altitude);
        return `${convertedAltitude.toFixed(2)} ${altitudeUnit.value}`;
    }
});

const soil = computed(()=>{
    if(!!payload.value){
        return `${payload.value.soilMoisture.toFixed(2)} %`;
    }
});

</script>


<style scoped>
/** CSS STYLE HERE */
    Figure {
        border: 2px solid black;
    }

    .custom-sheet {
        background-color: #f5f5f5;
        border-radius: 15px;
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    }

    .custom-text-field {
        background-color: #ffffff;
        border-radius: 8px;
    }

    .custom-btn {
        background-color: #e0e0e0;
        color: #160303;
        border-radius: 8px;
        transition: background-color 0.3s ease;
    }

    .custom-btn:hover {
        background-color: #1565c0;
    }

    .custom-card {
        background-color: #ffffff;
        border-radius: 15px;
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    }

    .custom-card-text {
        color: #1976d2;
    }

    .custom-chip {
        background-color: #e0e0e0;
        color: #333333;
        border-radius: 8px;
    }

    .custom-chart {
        background-color: #ffffff;
        border-radius: 15px;
        box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        overflow: hidden;
    }
</style>
  