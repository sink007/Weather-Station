 #!/usr/bin/python3


#################################################################################################################################################
#                                                    CLASSES CONTAINING ALL THE APP FUNCTIONS                                                                                                    #
#################################################################################################################################################


class DB:

    def __init__(self,Config):

        from math import floor
        from os import getcwd
        from os.path import join
        from json import loads, dumps, dump
        from datetime import timedelta, datetime, timezone 
        from pymongo import MongoClient , errors, ReturnDocument
        from urllib import parse
        from urllib.request import  urlopen 
        from bson.objectid import ObjectId  
       
      
        self.Config                         = Config
        self.getcwd                         = getcwd
        self.join                           = join 
        self.floor                      	= floor 
        self.loads                      	= loads
        self.dumps                      	= dumps
        self.dump                       	= dump  
        self.datetime                       = datetime
        self.ObjectId                       = ObjectId 
        self.server			                = Config.DB_SERVER
        self.port			                = Config.DB_PORT
        self.username                   	= parse.quote_plus(Config.DB_USERNAME)
        self.password                   	= parse.quote_plus(Config.DB_PASSWORD)
        self.remoteMongo                	= MongoClient
        self.ReturnDocument                 = ReturnDocument
        self.PyMongoError               	= errors.PyMongoError
        self.BulkWriteError             	= errors.BulkWriteError  
        self.tls                            = False # MUST SET TO TRUE IN PRODUCTION


    def __del__(self):
            # Delete class instance to free resources
            pass
 


    ####################
    # PROJECT UTIL FUNCTIONS  #
    ####################
    
    def addUpdate(self,data):
        '''ADD A NEW STORAGE LOCATION TO COLLECTION'''
        try:
            remotedb 	= self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password,self.server,self.port), tls=self.tls)
            result      = remotedb.ELET2415.project.insert_one(data)
        except Exception as e:
            msg = str(e)
            if "duplicate" not in msg:
                print("addUpdate error ",msg)
            return False
        else:                  
            return True
        
       

    def getAllInRange(self,start, end):
        '''RETURNS A LIST OF OBJECTS. THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start= int(start)
            end= int(end)
            remotedb 	= self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password,self.server,self.port), tls=self.tls)
            result = list(remotedb.ELET2415.project.find(
                    {
                    'timestamp': {
                        '$gte': start,
                        '$lte': end
                    }
                    },
                    {
                    '_id': 0,
                    'id': 1,
                    'timestamp': 1,
                    'temperature': 1,
                    'humidity': 1,
                    'heatindex': 1,
                    'pressure': 1,
                    'altitude': 1,
                    'soilMoisture': 1
                    }
                ).sort('timestamp', 1))
        except Exception as e:
            msg = str(e)
            print("getAllInRange error ",msg)            

        else:                  
            return result
        

    def humidityMMAR(self,start, end):
        '''RETURNS MIN, MAX, AVG AND RANGE FOR HUMIDITY. THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start= int(start)
            end= int(end)

            remotedb 	= self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password,self.server,self.port), tls=self.tls)
            result    = list(remotedb.ELET2415.project.aggregate(  [ {
                            '$match': {
                            'timestamp': { '$gte': start, '$lte': end }
                        }
                    },
                    {
                        '$group': {
                        '_id': 1,
                        'humidity': { '$push': '$$ROOT.humidity' }
                        }
                    },
  
                    {
                        '$project': {
                        '_id': 1,
                        'max': { '$max': '$humidity' },
                        'min': { '$min': '$humidity' },
                        'avg': { '$avg': '$humidity' },
                        'range': { '$subtract': [ { '$max': '$humidity' }, { '$min': '$humidity' } ] }
                        }
                    }]))

        except Exception as e:
            msg = str(e)
            print("humidityMMAS error ",msg)            
        else:                  
            return result
        
    def temperatureMMAR(self,start, end):
        '''RETURNS MIN, MAX, AVG AND RANGE FOR TEMPERATURE. THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start= int(start)
            end= int(end)
            remotedb 	= self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password,self.server,self.port), tls=self.tls)
            result      =list(remotedb.ELET2415.project.aggregate( [{
                            '$match': {
                            'timestamp': { '$gte': start, '$lte': end }
                        }
                    },
                    {
                        '$group': {
                        '_id': 1,
                        'temperature': { '$push': "$$ROOT.temperature" }
                        }
                    },
  
                    {
                        '$project': {
                        '_id': 1 ,
                        'max': { '$max': "$temperature" },
                        'min': { '$min': "$temperature" },
                        'avg': { '$avg': "$temperature" },
                        'range': { '$subtract': [ { '$max': "$temperature" }, { '$min': "$temperature" } ] }
                        }
                    }]))

        except Exception as e:
            msg = str(e)
            print("temperatureMMAS error ",msg)            
        else:                  
            return result
    
    def altitudeMMAR(self, start, end):
        '''RETURNS MIN, MAX, AVG AND RANGE FOR ALTITUDE THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start = int(start)
            end = int(end)
            remotedb = self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password, self.server, self.port), tls=self.tls)
            result = list(remotedb.ELET2415.project.aggregate([
                {
                    '$match': {
                        'timestamp': {'$gte': start, '$lte': end}
                    }
                },
                {
                    '$group': {
                        '_id': 1,
                        'altitude': {'$push': "$$ROOT.altitude"}
                    }
                },
                {
                    '$project': {
                        '_id': 1,
                        'max': {'$max': "$altitude"},
                        'min': {'$min': "$altitude"},
                        'avg': {'$avg': "$altitude"},
                        'range': {'$subtract': [{'$max': "$altitude"}, {'$min': "$altitude"}]}
                    }
                }
            ]))
        except Exception as e:
            msg = str(e)
            print("altitudeMMAR error ", msg)
        else:
            return result


    def pressureMMAR(self, start, end):
        '''RETURNS MIN, MAX, AVG AND RANGE FOR PRESSURE THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start = int(start)
            end = int(end)
            remotedb = self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password, self.server, self.port), tls=self.tls)
            result = list(remotedb.ELET2415.project.aggregate([
                {
                    '$match': {
                        'timestamp': {'$gte': start, '$lte': end}
                    }
                },
                {
                    '$group': {
                        '_id': 1,
                        'pressure': {'$push': "$$ROOT.pressure"}
                    }
                },
                {
                    '$project': {
                        '_id': 1,
                        'max': {'$max': "$pressure"},
                        'min': {'$min': "$pressure"},
                        'avg': {'$avg': "$pressure"},
                        'range': {'$subtract': [{'$max': "$pressure"}, {'$min': "$pressure"}]}
                    }
                }
            ]))
        except Exception as e:
            msg = str(e)
            print("pressureMMAR error ", msg)
        else:
            return result


    def soilMoistureMMAR(self, start, end):
        '''RETURNS MIN, MAX, AVG AND RANGE FOR SOIL MOISTURE THAT FALLS WITHIN THE START AND END DATE RANGE'''
        try:
            start = int(start)
            end = int(end)
            remotedb = self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password, self.server, self.port), tls=self.tls)
            result = list(remotedb.ELET2415.project.aggregate([
                {
                    '$match': {
                        'timestamp': {'$gte': start, '$lte': end}
                    }
                },
                {
                    '$group': {
                        '_id': 1,
                        'soilMoisture': {'$push': "$$ROOT.soilMoisture"}
                    }
                },
                {
                    '$project': {
                        '_id': 1,
                        'max': {'$max': "$soilMoisture"},
                        'min': {'$min': "$soilMoisture"},
                        'avg': {'$avg': "$soilMoisture"},
                        'range': {'$subtract': [{'$max': "$soilMoisture"}, {'$min': "$soilMoisture"}]}
                    }
                }
            ]))
        except Exception as e:
            msg = str(e)
            print("soilMoistureMMAR error ", msg)
        else:
            return result

    def frequencyDistro(self,variable,start, end):
        '''RETURNS THE FREQUENCY DISTROBUTION FOR A SPECIFIED VARIABLE WITHIN THE START AND END DATE RANGE'''
        try:
            start= int(start)
            end= int(end)
            remotedb 	= self.remoteMongo('mongodb://%s:%s@%s:%s' % (self.username, self.password,self.server,self.port), tls=self.tls)
            result = list(remotedb.ELET2415.project.aggregate([{
                            '$match': {
                            'timestamp': { '$gte': start, '$lte': end}
                            }
                        },
                     
                        {
                            '$bucket': {
                                'groupBy': f"${variable}",
                                'boundaries': [0, 20, 40, 60, 80, 100],
                                'default': 'outliers',
                                'output': {
                                    'count': { '$sum': 1 }
                                }
                            }
                        }]))

        except Exception as e:
            msg = str(e)
            print("frequencyDistro error ",msg)            
        else:                  
            return result
        
 



def main():
    from config import Config
    from time import time, ctime, sleep
    from math import floor
    from datetime import datetime, timedelta
    one = DB(Config)
 
 
    start = time() 
    end = time()
    print(f"completed in: {end - start} seconds")
    
if __name__ == '__main__':
    main()


    
