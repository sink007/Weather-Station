<template>
   <v-container class="container" fluid align="center" background-color="surface">
      <v-row class="row row1" max-width="1200px">
        <v-col class="col col1" cols="9" align="center">
            <figure class="highcharts-figure">
                <div id="container">
                </div>
            </figure>
        </v-col>
        <v-col class="col col2" cols="3" align="center"> 
            
            <VCard margin-bottom="5px" max-width="500px" color="primaryContainer" subtitle="Temperature">
                <v-card-item>
                     <span class="text-h3 text-onPrimaryContainer">{{ temperature }}</span>
                </v-card-item>
            </VCard>  

            <VCard margin-bottom="5px" max-width="500px" color="tertiaryContainer" subtitle="HeatIndex (Feels Like)">
                <v-card-item>
                    <span class="text-h3 text-onTertiaryContainer">{{ heatindex }}</span>
                </v-card-item>
            </VCard> 

            <VCard margin-bottom="5px" max-width="500px" color="secondaryContainer" subtitle="Humidity">
                <v-card-item>
                    <span class="text-h3 text-onSecondaryContainer">{{ humidity }}</span>
                </v-card-item>
            </VCard> 
        </v-col>
      </v-row>
      <v-row class="row row2" max-width="1200px" justify="start">
        <v-col class="col col1" cols="9" align="center"> 
            <figure class="highcharts-figure">
                <div id="container1">
                </div>
            </figure>
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
const points = ref(10); // Specify the quantity of points to be shown on the live graph simultaneously.
const shift = ref(false); // Delete a point from the left side and append a new point to the right side of the graph.
const AppStore = useAppStore();
const Mqtt = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);

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
            /*{
                name: 'Heat Index',
                type: 'spline',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1]
        }*/ ],
    });

    humHiChart.value = Highcharts.chart('container1', {
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
         ],
    });
}

// WATCHERS
watch(payload,(data)=> {
    if(points.value > 0){ points.value -- ; }
    else{ shift.value = true; }
    
    tempHiChart.value.series[0].addPoint({y:parseFloat(data.temperature.toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
    //tempHiChart.value.series[1].addPoint({y:parseFloat(data.heatindex.toFixed(2)) ,x: data.timestamp * 1000 },
    //true, shift.value);
    humHiChart.value.series[0].addPoint({y:parseFloat(data.humidity.toFixed(2)) ,x: data.timestamp * 1000 },
    true, shift.value);
})

const updateLineCharts = async ()=>{
    if(!!start.value && !!end.value){
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const data = await AppStore.getAllInRange(startDate,endDate);
        // Create arrays for each plot
        let temperature = [];
       // let heatindex = [];
        let humidity = [];
        // Iterate through data variable and transform object to format recognized by highcharts
        data.forEach(row => {
            temperature.push({"x": row.timestamp * 1000, "y": parseFloat(row.temperature.toFixed(2)) });
            //heatindex.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
            humidity.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
        });
        // Add data to Temperature and Heat Index chart
        tempHiChart.value.series[0].setData(temperature);
        tempHiChart.value.series[1].setData(heatindex);
        humHiChart.value.series[0].setData(humidity);
    }
}

// COMPUTED PROPERTIES
const temperature = computed(()=>{
    if(!!payload.value){
        return `${payload.value.temperature.toFixed(2)} °C`;
    }
});

const humidity = computed(()=>{
    if(!!payload.value){
        return `${payload.value.humidity.toFixed(2)} %`;
    }
});

const heatindex = computed(()=>{
    if(!!payload.value){
        return `${payload.value.heatindex.toFixed(2)} °C`;
    }
});

</script>


<style scoped>
/** CSS STYLE HERE */
Figure {
    border: 2px solid black;
}

</style>
  