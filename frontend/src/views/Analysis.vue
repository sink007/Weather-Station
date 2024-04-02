<template>
    <v-container class="container" fluid background-color="surface">
        <v-row class="row row1 pa-4" max-width="1200px">
            <v-col class="col col1" cols="2" align="center"> 
                <v-sheet class="pa-4 custom-sheet" height="250">
                    <v-divider></v-divider>
                    <v-text-field v-model="start" label="Start date" type="date" dense solo-inverted class="mr-5 custom-text-field" 
                            :style="{ maxWidth: '300px' }" flat
                            >
                    </v-text-field>
                    <v-text-field v-model="end" label="End date" type="date" dense solo-inverted
                        :style="{ maxWidth: '300px' }"
                        flat >
                    </v-text-field>
                    <v-spacer></v-spacer>
                    <VBtn @click="startAnalysis" text="Analyze" color="primary" variant="elevated" class="custom-btn">
                    </VBtn>
                </v-sheet>
            </v-col>
            <v-col class="col col2" cols="2" align="center"> 
                <v-card title="Temperature" variant="outlined" color="primary" width="300" density="compact" rounded="lg" class="custom-card">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="elevated">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ temperature.min }}</v-chip>
                                </template>
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ temperature.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ temperature.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold custom-card-text" > {{ temperature.avg }}</span>
                    </v-card-item>

                </v-card>
            </v-col>
            <v-col class="col col3" cols="2" align="center">
                <v-card title="Humidity" variant="outlined" color="primary" width="300" density="compact" rounded="lg" class="custom-card">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="elevated">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ humidity.min }}</v-chip>
                                </template>
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ humidity.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ humidity.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold custom-card-text" > {{ humidity.avg }}</span>
                    </v-card-item>
                </v-card>
            </v-col>
            <v-col class="col col4" cols="2" align="center">
                <v-card title="Pressure" variant="outlined" color="primary" width="300" density="compact" rounded="lg" class="custom-card">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="elevated">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ pressure.min }}</v-chip>
                                </template>
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ pressure.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ pressure.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold custom-card-text" > {{ pressure.avg }}</span>
                    </v-card-item>
                </v-card>
            </v-col>
            <v-col class="col col5" cols="2" align="center">
                <v-card title="Altitude" variant="outlined" color="primary" width="300" density="compact" rounded="lg" class="custom-card">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="elevated">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ altitude.min }}</v-chip>
                                </template>
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ altitude.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ altitude.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold custom-card-text" > {{ altitude.avg }}</span>
                    </v-card-item>
                </v-card>
            </v-col>
            <v-col class="col col6" cols="2" align="center">
                <v-card title="Soil Moisture" variant="outlined" color="primary" width="300" density="compact" rounded="lg" class="custom-card">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="elevated">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ soilM.min }}</v-chip>
                                </template>
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ soilM.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props" class="custom-chip"> {{ soilM.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold custom-card-text" > {{ soilM.avg }}</span>
                    </v-card-item>
                </v-card>
            </v-col>

        </v-row>
        <v-row class="row row2" max-width="1200px">
            <v-col class="col col4" align="center" cols="12" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container"></div>
                </figure>
            </v-col>
        </v-row>
        <v-row class="row row3" max-width="1200px">
            <v-col class="col col1" align="center" cols="6" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container0"></div>
                </figure>
            </v-col>
            <v-col class="col col2" align="center" cols="6" > 
                <figure class="highcharts-figure custom-chart">
                    <div id="container3"></div>
                </figure>
            </v-col>
        </v-row>
        <v-row class="row row4" max-width="1200px">
            <v-col class="col col7" align="center" cols="6" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container1"></div>
                </figure>
            </v-col>
            <v-col class="col col8" align="center" cols="6" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container2"></div>
                </figure>
            </v-col>
        </v-row>
        <v-row class="row row5" max-width="1200px">
            <v-col class="col col1" align="center" cols="6" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container5"></div>
                </figure>
            </v-col>
            <v-col class="col col2" align="center" cols="6" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container6"></div>
                </figure>
            </v-col>
            <v-col class="col col3" align="center" cols="12" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container7"></div>
                </figure>
            </v-col>
            <v-col class="col col4" align="center" cols="12" >
                <figure class="highcharts-figure custom-chart">
                    <div id="container4"></div>
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
import Highcharts from 'highcharts';
import more from 'highcharts/highcharts-more';
import Exporting from 'highcharts/modules/exporting';
import { useAppStore } from "@/store/appStore";
import { useMqttStore } from '@/store/mqttStore'; // Import Mqtt Store
import { storeToRefs } from "pinia";

Exporting(Highcharts);
more(Highcharts);
// IMPORTS

// VARIABLES
const AppStore = useAppStore();
const Mqtt = useMqttStore();
const { payload, payloadTopic } = storeToRefs(Mqtt);
// VARIABLES
const router      = useRouter();
const route       = useRoute();  
const start = ref(""); 
const end = ref("");
const tempHiChart= ref(null);
const humHiChart= ref(null);
const pressChart= ref(null);
const altChart= ref(null);
const soilChart= ref(null);
const freq= ref(null);
const scatterTH= ref(null);
const scatterHH= ref(null);
const pressalt= ref(null);
const temperature= reactive({"min":0,"max":0,"avg":0,"range":0});
const humidity= reactive({"min":0,"max":0,"avg":0,"range":0});
const pressure= reactive({"min":0,"max":0,"avg":0,"range":0});
const altitude= reactive({"min":0,"max":0,"avg":0,"range":0});
const soilM= reactive({"min":0,"max":0,"avg":0,"range":0});

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

    startAnalysis();
});


onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});

const startAnalysis = () => {
      updateLineCharts();
      updateScatterCharts();
      updateCards();
      updateHistogramCharts();
      
      // Start auto-refresh every 15 seconds
      setInterval(() => {
        updateLineCharts();
        updateScatterCharts();
        updateCards();
        updateHistogramCharts();
      }, 15000);
};
const CreateCharts = async () => {
// TEMPERATURE CHART
    tempHiChart.value = Highcharts.chart("container", {
            chart: { zoomType: "x" },
            title: { text: "Air Temperature and Heat Index Analysis", align: "left" },
            subtitle: {
                text:
                    " The heat index, also known as the apparent temperature, is a measure that combines air temperature and relative humidity to assess how hot it feels to the human body. " +
                    "The relationship between heat index and air temperature is influenced by humidity levels. As humidity increases, the heat" +
                    "index also rises, making the perceived temperature higher than the actual air temperature.",
            },
            yAxis: {
                title: {
                    text: "Air Temperature & Heat Index",
                    style: { color: "#000000" },
                },
                labels: { format: "{value} °C" },
            },

            tooltip: {
                pointFormat: "Heatindex: {point.x} °C <br/> Temperature: {point.y} °C",
            },

            xAxis: {
                type: "datetime",
                title: { text: "Time", style: { color: "#000000" } },
            },
            tooltip: { shared: true },
            series: [
                {
                    name: "Temperature",
                    type: "line",
                    data: [],
                    turboThreshold: 0,
                    color: Highcharts.getOptions().colors[0],
                },
                {
                    name: "Heat Index",
                    type: "line",
                    data: [],
                    turboThreshold: 0,
                    color: Highcharts.getOptions().colors[1],
                },
            ],
    });

    humHiChart.value = Highcharts.chart("container0", {
        chart: { zoomType: "x" },
        title: { text: "Humidity Analysis", align: "left" },
        subtitle:{text:'Visualize the humidity readings across the specified time period'},
        yAxis: {
            title: {
                text: "Humidity",
                style: { color: "#000000" },
            },
            labels: { format: "{value} %" },
        },

        tooltip: {
            pointFormat: "Humidity: {point.x} % "
        },
        xAxis: {
            type: "datetime",
            title: { text: "Time", style: { color: "#000000" } },
        },
        tooltip: { shared: true },
        series: [
            {
                name: "Humidity",
                type: "line",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[3],
            },
        ],
    });

        // Pressure Chart
    pressChart.value = Highcharts.chart("container1", {
        chart: { zoomType: "x" },
        title: { text: "Pressure Analysis", align: "left" },
        subtitle:{text:'Visualize the pressure readings across the specified time period'},
        yAxis: {
            title: {
                text: "Pressure",
                style: { color: "#000000" },
            },
            labels: { format: "{value} Pa" }, // Adjust unit as per your data
        },
        tooltip: {
            pointFormat: "Pressure: {point.y} Pa" // Adjust tooltip format as per your data
        },
        xAxis: {
            type: "datetime",
            title: { text: "Time", style: { color: "#000000" } },
        },
        tooltip: { shared: true },
        series: [
            {
                name: "Pressure",
                type: "line",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[4],
            },
        ],
    });

    // Altitude Chart
    altChart.value = Highcharts.chart("container2", {
        chart: { zoomType: "x" },
        title: { text: "Altitude Analysis", align: "left" },
        subtitle:{text:'Visualize the altitude readings across the specified time period'},
        yAxis: {
            title: {
                text: "Altitude",
                style: { color: "#000000" },
            },
            labels: { format: "{value} m" }, // Adjust unit as per your data
        },
        tooltip: {
            pointFormat: "Altitude: {point.y} m" // Adjust tooltip format as per your data
        },
        xAxis: {
            type: "datetime",
            title: { text: "Time", style: { color: "#000000" } },
        },
        tooltip: { shared: true },
        series: [
            {
                name: "Altitude",
                type: "line",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[5],
            },
        ],
    });

    // Soil Moisture Chart
    soilChart.value = Highcharts.chart("container3", {
        chart: { zoomType: "x" },
        title: { text: "Soil Moisture Analysis", align: "left" },
        subtitle:{text:'Visualize the soil moisture readings across the specified time period'},
        yAxis: {
            title: {
                text: "Soil Moisture",
                style: { color: "#000000" },
            },
            labels: { format: "{value} %" }, // Adjust unit as per your data
        },
        tooltip: {
            pointFormat: "Soil Moisture: {point.y} %" // Adjust tooltip format as per your data
        },
        xAxis: {
            type: "datetime",
            title: { text: "Time", style: { color: "#000000" } },
        },
        tooltip: { shared: true },
        series: [
            {
                name: "Soil Moisture",
                type: "line",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[6],
            },
        ],
    });


    freq.value = Highcharts.chart("container4", {
        chart: { zoomType: "x" },
        title: { text: "Frequency Distribution Analysis", align: "left" },
        yAxis: {
            title: {
                text: "Frequency",
                style: { color: "#000000" },
            },
            labels: { format: "{value}" },
        },

        xAxis: {
            title: { text: "ID", style: { color: "#000000" } },
        },

        tooltip: { shared: true },

        series: [
            {
                name: "Temperature",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0],
            },
            {
                name: "Humidity",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1],
            },
            {
                name: "Heat Index",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[2],
            },
            {
                name: "Altitude",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[3],
            },
            {
                name: "Pressure",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[4],
            },
            {
                name: "Soil Moisture",
                type: "column",
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[5],
            }
        ]
    });


    scatterTH.value = Highcharts.chart('container5', {
        chart: { zoomType: 'x' },
        series: {
           name: {text: 'Analysis'}
        },

        title: { text: 'Temperature & Heat Index Correlation Analysis', align: 'left' },
        
        subtitle:{text:'Visualize the relationship between Temperature and Heat Index as well as revealing patterns or trends in the data'},
        
        yAxis: {
            title: { text: 'Heat Index' , style:{color:'#000000'}},
            labels: { format: '{value} °C' }
        },
            xAxis: {
            type: 'linear',
            title: { text: 'Temperature', style:{color:'#000000'} },
            labels: { format: '{value} °C' }
        },

        tooltip: { shared:true,
            pointFormat: "Temperature: {point.x} °C <br/> Heat Index: {point.y} °C"
        },

        series: [
            {
                name: 'Temperature',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[9]
            },
            {
                name: 'HeatIndex',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1]
            },
         ],
    });
    
    pressalt.value = Highcharts.chart('container7', {
        chart: { zoomType: 'x' },
        series: {
           name: {text: 'Analysis'}
        },

        title: { text: 'Pressure & Altitude Correlation Analysis', align: 'left' },
        
        subtitle:{text:'Visualize the relationship between Pressure and Altitude as well as revealing patterns or trends in the data'},
        
        yAxis: {
            title: { text: 'Altitude' , style:{color:'#000000'}},
            labels: { format: '{value} m' }
        },
            xAxis: {
            type: 'linear',
            title: { text: 'Pressure', style:{color:'#000000'} },
            labels: { format: '{value} kPa' }
        },

        tooltip: { shared:true,
            pointFormat: "Pressure: {point.x} kPa <br/> Altitude: {point.y} m"
        },

        series: [
            {
                name: 'Altitude',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[12]
            },
            {
                name: 'Pressure',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1]
            },
         ],
    });

    scatterHH.value = Highcharts.chart('container6', {
        chart: { zoomType: 'x' },
        series: {
           name: {text: 'Analysis'}
        },
        
        title: { text: 'Humidity & Heat Index Correlation Analysis', align: 'left' },
        
        subtitle:{text:'Visualize the relationship between Humidity and Heat Index as well as revealing patterns or trends in the data'},
        
        yAxis: {
            title: { text: 'Heat Index' , style:{color:'#000000'}},
            labels: { format: '{value} °C' }
        },
            xAxis: {
            type: 'linear',
            title: { text: 'Humidity', style:{color:'#000000'} },
            labels: { format: '{value} %' }
        },

        tooltip: { shared:true,
            pointFormat: "Humidity: {point.x} % <br/> Heat Index: {point.y} °C"
        },

        series: [
            {
                name: 'Humidity',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[0]
            },
            {
                name: 'HeatIndex',
                type: 'scatter',
                data: [],
                turboThreshold: 0,
                color: Highcharts.getOptions().colors[1]
            },
         ],
    });

}

const updateLineCharts = async ()=>{
    if(!!start.value && !!end.value){
        tempHiChart.value.series[0].setData([],true);
        tempHiChart.value.series[1].setData([],true);
        pressChart.value.series[0].setData([],true);
        altChart.value.series[0].setData([],true);
        humHiChart.value.series[0].setData([],true);
        soilChart.value.series[0].setData([],true);
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const data = await AppStore.getAllInRange(startDate,endDate);
        console.log(data);
        // Create arrays for each plot
        let temp = [];
        let heat = [];
        let hum = [];
        let press=[];
        let alt=[];
        let soil=[];
        // Iterate through data variable and transform object to format recognized by highcharts
        data.forEach(row => {
            temp.push({"x": row.timestamp * 1000, "y": parseFloat(row.temperature.toFixed(2)) });
            heat.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
            hum.push({ "x": row.timestamp * 1000,"y": parseFloat(row.humidity.toFixed(2)) });
            press.push({ "x": row.timestamp * 1000, "y": parseFloat(row.pressure.toFixed(2)) }); 
            alt.push({ "x": row.timestamp * 1000, "y": parseFloat(row.altitude.toFixed(2)) }); 
            soil.push({ "x": row.timestamp * 1000, "y": parseFloat(row.soilMoisture.toFixed(2)) }); 

        });
        console.log(temperature);
        // Add data to Temperature and Heat Index chart. DO LATEERRRR
        tempHiChart.value.series[0].setData(temp);
        tempHiChart.value.series[1].setData(heat);
        humHiChart.value.series[0].setData(hum);
        pressChart.value.series[0].setData(press);
        altChart.value.series[0].setData(alt);
        soilChart.value.series[0].setData(soil);
        /*scatterTH.value.series[0].setData(heatindex);
        scatterTH.value.series[1].setData(temperature);
        scatterHH.value.series[0].setData(heatindex);
        scatterHH.value.series[1].setData(humidity);*/
    }
}

const updateCards = async () => {
    // Retrieve Min, Max, Avg, Spread/Range
    if(!!start.value && !!end.value){
        // 1. Convert start and end dates collected fron TextFields to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // 2. Fetch data from backend by calling the API functions
        const temp = await AppStore.getTemperatureMMAR(startDate,endDate);
        const humid = await AppStore.getHumidityMMAR(startDate,endDate);
        const alt = await AppStore.getAltitudeMMAR(startDate,endDate);
        const press = await AppStore.getPressureMMAR(startDate,endDate);
        const soil = await AppStore.getSoilMoistureMMAR(startDate,endDate);
        console.log(temp);
        console.log(humid);
        temperature.max = temp[0].max.toFixed(1);
        //3. complete for min, avg and range
        temperature.min = temp[0].min.toFixed(1);
        temperature.avg = temp[0].avg.toFixed(1);
        temperature.range = temp[0].range.toFixed(1);
        humidity.max = humid[0].max.toFixed(1);
        humidity.min = humid[0].min.toFixed(1);
        humidity.avg = humid[0].avg.toFixed(1);
        humidity.range = humid[0].range.toFixed(1);
        pressure.max = press[0].max.toFixed(1);
        pressure.min = press[0].min.toFixed(1);
        pressure.avg = press[0].avg.toFixed(1);
        pressure.range = press[0].range.toFixed(1);
        altitude.max = alt[0].max.toFixed(1);
        altitude.min = alt[0].min.toFixed(1);
        altitude.avg = alt[0].avg.toFixed(1);
        altitude.range = alt[0].range.toFixed(1);
        soilM.max = soil[0].max.toFixed(1);
        soilM.min = soil[0].min.toFixed(1);
        soilM.avg = soil[0].avg.toFixed(1);
        soilM.range = soil[0].range.toFixed(1);

    }
}

const updateScatterCharts = async () => {
  if (!!start.value && !!end.value) {
    scatterTH.value.series[0].setData([],true);
    scatterHH.value.series[0].setData([],true);
    pressalt.value.series[0].setData([],true);
    // Convert output from Textfield components to 10 digit timestamps
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    // Fetch data from backend
    const data = await AppStore.getAllInRange(startDate, endDate);
    // Create arrays for each plot
    let tempheat = [];
    let humheat= [];
    let prealt=[];
    // Iterate through data variable and transform object to format recognized by highcharts
    data.forEach((row) => {
        tempheat.push({
            x: parseFloat(row.temperature.toFixed(2)),
            y: parseFloat(row.heatindex.toFixed(2)),
        });
    });

    data.forEach((row) => {
        humheat.push({
            x: parseFloat(row.humidity.toFixed(2)),
            y: parseFloat(row.heatindex.toFixed(2)),
        });

    
    });

    data.forEach((row) => {
        prealt.push({
            x: parseFloat(row.pressure.toFixed(2)),
            y: parseFloat(row.altitude.toFixed(2)),
        });
    });

    scatterTH.value.series[0].setData(tempheat);
    scatterHH.value.series[0].setData(humheat);
    pressalt.value.series[0].setData(prealt);
  }
};

const updateHistogramCharts = async () =>{
    // Retrieve Min, Max, Avg, Spread/Range for Column graph
    if(!!start.value && !!end.value){
        freq.value.series[0].setData([],true);
        // 8. update series[1] for the histogram/Column chart with humidity data
        freq.value.series[1].setData([],true);
        // 9. update series[2] for the histogram/Column chart with heat index data
        freq.value.series[2].setData([],true);
        freq.value.series[3].setData([],true);
        freq.value.series[4].setData([],true);
        freq.value.series[5].setData([],true);
        // 1. Convert start and end dates collected fron TextFields to 10 digit timestamps
        // Subsequently, create startDate and endDate variables and then save the respective timestamps in these variables
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        console.log(startDate);
        console.log(endDate);
        // 2. Fetch data(temp, humid and hi) from backend by calling the getFreqDistro API functions for each
        const temp = await AppStore.getFreqDistro("temperature",startDate,endDate);
        const humid = await AppStore.getFreqDistro("humidity",startDate ,endDate );
        const hi = await AppStore.getFreqDistro("heatindex",startDate,endDate );
        const alt = await AppStore.getFreqDistro("altitude",startDate,endDate );
        const press = await AppStore.getFreqDistro("pressure",startDate,endDate );
        const soil = await AppStore.getFreqDistro("soilMoisture",startDate,endDate );
        // 3. create an empty array for each variable (temperature, humidity and heatindex)
        // see example below
        let temperature = [];
        let humidity = [];
        let heatIndex = [];
        let altitude = [];
        let pressure = [];
        let soilM = [];
        // 4. Iterate through the temp variable, which contains temperature data fetched from the backend
        // transform the data to {"x": x_value,"y": y_value} format and then push it to the temperature array created previously
        // see example below
        temp.forEach(row => {
            temperature.push({"x": row["_id"],"y": row["count"]})
        });

        humid.forEach(row => {
            humidity.push({"x": row["_id"],"y": row["count"]})
        });
    
        hi.forEach(row => {
            heatIndex.push({"x": row["_id"],"y": row["count"]})
        });

        alt.forEach(row => {
            altitude.push({"x": row["_id"],"y": row["count"]})
        });

        press.forEach(row => {
            pressure.push({"x": row["_id"],"y": row["count"]})
        });

        soil.forEach(row => {
            soilM.push({"x": row["_id"],"y": row["count"]})
        });
        // 7. update series[0] for the histogram/Column chart with temperature data
        // see example below
        console.log(altitude);
        freq.value.series[0].setData(temperature);
        // 8. update series[1] for the histogram/Column chart with humidity data
        freq.value.series[1].setData(humidity);
        // 9. update series[2] for the histogram/Column chart with heat index data
        freq.value.series[2].setData(heatIndex);
        freq.value.series[3].setData(altitude);
        freq.value.series[4].setData(pressure);
        freq.value.series[5].setData(soilM);
    }
}
// COMPUTED PROPERTIES

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
        background-color: #1976d2;
        color: #ffffff;
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