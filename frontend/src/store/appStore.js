import {defineStore} from 'pinia'
import {ref} from 'vue'


export const useAppStore =  defineStore('app', ()=>{

    /*  
    The composition API way of defining a Pinia store
    ref() s become state properties
    computed() s become getters
    function() s become actions  
    */ 

    // STATES 
  


    // ACTIONS
    const getAllInRange = async (start,end)=>{
        // FETCH REQUEST WILL TIMEOUT AFTER 20 SECONDS
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(()=>{controller.abort()},60000);
        const URL = `/api/project/get/${start}/${end}`;
        try {
            const response = await fetch(URL,{ method: 'GET', signal: signal });
            if (response.ok){
                const data = await response.json();
                let keys = Object.keys(data);
                if(keys.includes("status")){
                    if(data["status"] == "found" ){
                        // console.log(data["data"] )
                        return data["data"];
                    }
                    if(data["status"] == "failed"){
                        console.log("getAllInRange returned no data");
                    }
                }
            }
            else{
                const data = await response.text();
                console.log(data);
            }
        }

        catch(err){
            console.error('getAllInRange error: ', err.message);
        }
        return []
    }

    const getTemperatureMMAR = async (start,end)=>{
        // FETCH REQUEST WILL TIMEOUT AFTER 20 SECONDS
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(()=>{controller.abort()},60000);
        const URL = `/api/mmar/temperature/${start}/${end}`;
        try {
            const response = await fetch(URL,{ method: 'GET', signal: signal });
            if (response.ok){
                const data = await response.json();
                let keys = Object.keys(data);
                if(keys.includes("status")){
                    if(data["status"] == "found" ){
                        console.log(data["data"] )
                        return data["data"];
                    }
                    if(data["status"] == "failed" ){
                        console.log("Cant get temp");
                    }
                }
             }
            else{
                const data = await response.text();
                console.log(data);
            }
        }
        catch(err){
             console.error('getTemperatureMMAR error: ', err.message);
        }
        return []
    }

    const getHumidityMMAR = async (start,end)=>{
        // FETCH REQUEST WILL TIMEOUT AFTER 20 SECONDS
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(()=>{controller.abort()},60000);
        const URL = `/api/mmar/humidity/${start}/${end}`;
        try {
            const response = await fetch(URL,{ method: 'GET', signal: signal });
             if (response.ok){
                const data = await response.json();
                let keys = Object.keys(data);
                if(keys.includes("status")){
                    if(data["status"] == "found" ){
                        console.log(data["data"] )
                        return data["data"];
                    }
                    if(data["status"] == "failed" ){
                        console.log("Cant get hum");
                    }
                }
             }
            else{
                const data = await response.text();
                console.log(data);
            }
        }
        catch(err){
             console.error('getHumidityMMAR error: ', err.message);
        }
        return []
    }

    const getPressureMMAR = async (start, end) => {
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(() => { controller.abort(); }, 60000);
        const URL = `/api/mmar/pressure/${start}/${end}`;
        
        try {
            const response = await fetch(URL, { method: 'GET', signal: signal });
            if (response.ok) {
                const data = await response.json();
                let keys = Object.keys(data);
                if (keys.includes("status")) {
                    if (data["status"] === "found") {
                        console.log(data["data"]);
                        return data["data"];
                    }
                    if (data["status"] === "failed") {
                        console.log("Cannot get pressure data");
                    }
                }
            } else {
                const data = await response.text();
                console.log(data);
            }
        } catch (err) {
            console.error('getPressureMMAR error: ', err.message);
        }
        return [];
    };
    
    const getAltitudeMMAR = async (start, end) => {
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(() => { controller.abort(); }, 60000);
        const URL = `/api/mmar/altitude/${start}/${end}`;
        
        try {
            const response = await fetch(URL, { method: 'GET', signal: signal });
            if (response.ok) {
                const data = await response.json();
                let keys = Object.keys(data);
                if (keys.includes("status")) {
                    if (data["status"] === "found") {
                        console.log(data["data"]);
                        return data["data"];
                    }
                    if (data["status"] === "failed") {
                        console.log("Cannot get altitude data");
                    }
                }
            } else {
                const data = await response.text();
                console.log(data);
            }
        } catch (err) {
            console.error('getAltitudeMMAR error: ', err.message);
        }
        return [];
    };
    
    const getSoilMoistureMMAR = async (start, end) => {
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(() => { controller.abort(); }, 60000);
        const URL = `/api/mmar/soilMoisture/${start}/${end}`;
        
        try {
            const response = await fetch(URL, { method: 'GET', signal: signal });
            if (response.ok) {
                const data = await response.json();
                let keys = Object.keys(data);
                if (keys.includes("status")) {
                    if (data["status"] === "found") {
                        console.log(data["data"]);
                        return data["data"];
                    }
                    if (data["status"] === "failed") {
                        console.log("Cannot get soil moisture data");
                    }
                }
            } else {
                const data = await response.text();
                console.log(data);
            }
        } catch (err) {
            console.error('getSoilMoistureMMAR error: ', err.message);
        }
        return [];
    };

    const getFreqDistro = async (variable,start,end)=>{
        // FETCH REQUEST WILL TIMEOUT AFTER 20 SECONDS
        const controller = new AbortController();
        const signal = controller.signal;
        const id = setTimeout(()=>{controller.abort()},60000);
        const URL = `/api/frequency/${variable}/${start}/${end}`;
        try {
            const response = await fetch(URL,{ method: 'GET', signal: signal });
             if (response.ok){
                const data = await response.json();
                let keys = Object.keys(data);
                if(keys.includes("status")){
                    if(data["status"] == "found" ){
                        console.log(data["data"] )
                        return data["data"];
                    }
                    if(data["status"] == "failed" ){
                        console.log("Cant get freq");
                    }
                }
             }
            else{
                const data = await response.text();
                console.log(data);
            }
        }
        catch(err){
             console.error('getFreqDistro error: ', err.message);
        }
        return []
    }


    return { 
        // EXPORTS	
        getAllInRange,
        getTemperatureMMAR,
        getHumidityMMAR,
        getPressureMMAR,
        getAltitudeMMAR,
        getSoilMoistureMMAR,
        getFreqDistro
    }
},{ persist: true  });