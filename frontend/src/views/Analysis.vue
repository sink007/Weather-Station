<template>
    <v-container class="container" fluid background-color="surface">
        <v-row class="row row1 pa-2" max-width="1200px">
            <v-col class="col col1" align="center"> 
                <v-sheet class="pa-2" height="250">
                    <p>Enter date range for Analysis</p>
                    <v-divider></v-divider>
                    <v-text-field v-model="start" label="Start date" type="date" dense solo-inverted class="mr-5" 
                            :style="{ maxWidth: '300px' }" flat
                            >
                    </v-text-field>
                    <v-text-field v-model="end" label="End date" type="date" dense solo-inverted
                        :style="{ maxWidth: '300px' }"
                        flat >
                    </v-text-field>
                    <v-spacer></v-spacer>
                    <VBtn @click="updateLineCharts(); updateScatterCharts(); updateCards(); updateHistogramCharts(); " text="Analyze" color="primary" variant="tonal" >
                    </VBtn>
                        
                </v-sheet>
            </v-col>
            <v-col class="col col2" align="center"> 
                <v-card title="Temperature" variant="outlined" color="primary" width="250" density="compact" rounded="lg">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ temperature.min }}</v-chip>
                                </template>
                            
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ temperature.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ temperature.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold" > {{ temperature.avg }}</span>
                    </v-card-item>

                </v-card>

            </v-col>
            <v-col class="col col3" align="center">
                <v-card title="Humidity" variant="outlined" color="primary" width="250" density="compact" rounded="lg">
                    <v-card-item class="mb-n5">
                        <v-chip-group class="d-flex flex-row justify-center" color="primaryContainer" variant="flat">
                            
                            <v-tooltip text="Min" location="start">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ humidity.min }}</v-chip>
                                </template>
                            
                            </v-tooltip> 

                            <v-tooltip text="Range" location="top">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ humidity.range }}</v-chip>
                                </template>
                            </v-tooltip>

                            <v-tooltip text="Max" location="end">
                                <template v-slot:activator="{props}">
                                    <v-chip v-bind="props"> {{ humidity.max }}</v-chip>
                                </template>
                            </v-tooltip>

                        </v-chip-group>

                    </v-card-item>
                    <v-card-item align="center">
                        <span class="text-h1 text-primary font-weight-bold" > {{ humidity.avg }}</span>
                    </v-card-item>
                </v-card>
            </v-col>

        </v-row>
        <v-row class="row row2" max-width="1200px">
            <v-col class="col col4" align="center" cols="12" >
                <figure class="highcharts-figure">
                    <div id="container"></div>
                </figure>
            </v-col>
            <v-col class="col col5" align="center" cols="12" > 
                <figure class="highcharts-figure">
                    <div id="container0"></div>
                </figure>
            </v-col>

        </v-row>
        <v-row class="row row3" max-width="1200px">
            <v-col class="col col6 border" align="center" cols="12" >
                <figure class="highcharts-figure">
                    <div id="container1"></div>
                </figure>
            </v-col>
            <v-col class="col col7" align="center" cols="12" >
                <figure class="highcharts-figure">
                    <div id="container2"></div>
                </figure>
            </v-col>
            <v-col class="col col8" align="center" cols="12" >
                <figure class="highcharts-figure">
                    <div id="container3"></div>
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
const columnTHH= ref(null);
const scatterTH= ref(null);
const scatterHH= ref(null);
const temperature= reactive({"min":0,"max":0,"avg":0,"range":0});
const humidity= reactive({"min":0,"max":0,"avg":0,"range":0});

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
});


onBeforeUnmount(()=>{
    // THIS FUNCTION IS CALLED RIGHT BEFORE THIS COMPONENT IS UNMOUNTED
    Mqtt.unsubcribeAll();
});

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
                color: Highcharts.getOptions().colors[0],
            },
        ],
    });

    columnTHH.value = Highcharts.chart("container1", {
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
                color: Highcharts.getOptions().colors[3],
            },
        ]
    });


    scatterTH.value = Highcharts.chart('container2', {
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

    scatterHH.value = Highcharts.chart('container3', {
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
        // Convert output from Textfield components to 10 digit timestamps
        let startDate = new Date(start.value).getTime() / 1000;
        let endDate = new Date(end.value).getTime() / 1000;
        // Fetch data from backend
        const data = await AppStore.getAllInRange(startDate,endDate);
        console.log(data)
        // Create arrays for each plot
        let temperature = [];
        let heatindex = [];
        let humidity = [];
        // Iterate through data variable and transform object to format recognized by highcharts
        data.forEach(row => {
            temperature.push({"x": row.timestamp * 1000, "y": parseFloat(row.temperature.toFixed(2)) });
            heatindex.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
            humidity.push({ "x": row.timestamp * 1000,"y": parseFloat(row.humidity.toFixed(2)) });
        });

        // Add data to Temperature and Heat Index chart. DO LATEERRRR
        tempHiChart.value.series[0].setData(temperature);
        tempHiChart.value.series[1].setData(heatindex);
        humHiChart.value.series[0].setData(humidity);
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
        console.log(temp);
        console.log(humid);
        temperature.max = temp[0].max.toFixed(1);
        //3. complete for min, avg and range
        temperature.min = temp[0].min.toFixed(1);
        temperature.avg = temp[0].avg.toFixed(1);
        temperature.range = temp[0].range.toFixed(1);
        //4. complete max, min, avg and range for the humidity variable
        humidity.max = humid[0].max.toFixed(1);
        humidity.min = humid[0].min.toFixed(1);
        humidity.avg = humid[0].avg.toFixed(1);
        humidity.range = humid[0].range.toFixed(1);
    }
}

const updateScatterCharts = async () => {
  if (!!start.value && !!end.value) {
    // Convert output from Textfield components to 10 digit timestamps
    let startDate = new Date(start.value).getTime() / 1000;
    let endDate = new Date(end.value).getTime() / 1000;
    // Fetch data from backend
    const data = await AppStore.getAllInRange(startDate, endDate);
    // Create arrays for each plot
    let tempheat = [];
    let humheat= [];
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
    
    scatterTH.value.series[0].setData(tempheat);
    scatterHH.value.series[0].setData(humheat);
  }
};

const updateHistogramCharts = async () =>{
    // Retrieve Min, Max, Avg, Spread/Range for Column graph
    if(!!start.value && !!end.value){
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
        // 3. create an empty array for each variable (temperature, humidity and heatindex)
        // see example below
        let temperature = [];
        let humidity = [];
        let heatIndex = [];
        // 4. Iterate through the temp variable, which contains temperature data fetched from the backend
        // transform the data to {"x": x_value,"y": y_value} format and then push it to the temperature array created previously
        // see example below
        temp.forEach(row => {
            temperature.push({"x": row["_id"],"y": row["count"]})
        });

        // 5. Iterate through the humid variable, which contains humidity data fetched from the backend
        // transform the data to {"x": x_value,"y": y_value} format and then push it to the humidity array created previously
        humid.forEach(row => {
            humidity.push({"x": row["_id"],"y": row["count"]})
        });
        // 6. Iterate through the humid variable, which contains heat index data fetched from the backend
        // transform the data to {"x": x_value,"y": y_value} format and then push it to the heatindex array created previously
        hi.forEach(row => {
            heatIndex.push({"x": row["_id"],"y": row["count"]})
        });
        // 7. update series[0] for the histogram/Column chart with temperature data
        // see example below
        console.log(temperature);
        columnTHH.value.series[0].setData(temperature);
        // 8. update series[1] for the histogram/Column chart with humidity data
        columnTHH.value.series[1].setData(humidity);
        // 9. update series[2] for the histogram/Column chart with heat index data
        columnTHH.value.series[2].setData(heatIndex);
    }
}
// COMPUTED PROPERTIES

</script>


<style scoped>
/** CSS STYLE HERE */
Figure {
    border: 2px solid black;
}

</style>
  
