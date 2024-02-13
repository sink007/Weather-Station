import { start, end, heatindex } from "./Analysis.vue";

export const updateLineCharts = async () => {
if (!!start.value && !!end.value) {
// Convert output from Textfield components to 10 digit timestamps
let startDate = new Date(start.value).getTime() / 1000;
let endDate = new Date(end.value).getTime() / 1000;
// Fetch data from backend
const data = await AppStore.getAllInRange(startDate, endDate);
// Create arrays for each plot
let temperature = [];
// let heatindex = [];
let humidity = [];
// Iterate through data variable and transform object to format recognized by highcharts
data.forEach(row => {
temperature.push({ "x": row.timestamp * 1000, "y": parseFloat(row.temperature.toFixed(2)) });
//heatindex.push({ "x": row.timestamp * 1000,"y": parseFloat(row.heatindex.toFixed(2)) });
humidity.push({ "x": row.timestamp * 1000, "y": parseFloat(row.heatindex.toFixed(2)) });
});
// Add data to Temperature and Heat Index chart
tempChart.value.series[0].setData(temperature);
tempChart.value.series[1].setData(heatindex);
humHiChart.value.series[0].setData(humidity);
}
};
