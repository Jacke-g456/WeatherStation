"""
Flask Documentation:     https://flask.palletsprojects.com/
Jinja2 Documentation:    https://jinja.palletsprojects.com/
Werkzeug Documentation:  https://werkzeug.palletsprojects.com/
This file creates your application.
"""

# from crypt import methods
import site 

from app import app, Config,  mongo, Mqtt
from flask import escape, render_template, request, jsonify, send_file, redirect, make_response, send_from_directory 
from json import dumps, loads 
from werkzeug.utils import secure_filename
from datetime import datetime,timedelta, timezone
from os import getcwd
from os.path import join, exists
from time import time, ctime
from math import floor
 



#####################################
#   Routing for your application    #
#####################################


#adds data to database collection weather
@app.route('/api/weather', methods=['POST'])
def update_weather():
    if request.method == 'POST':
        try:
            data = request.get_json()
            data["timestamp"] = floor(datetime.now().timestamp())
            Mqtt.publish("620165845",mongo.dumps(data))
            Mqtt.publish("620165845_pub",mongo.dumps(data))
            Mqtt.publish("620165845_sub",mongo.dumps(data))

            print(f"MQTT: {data}")

            success=mongo.insertData(data)
            if success:
                return jsonify({"status": "complete", "data": "complete"})


        except Exception as e:   
            print(f"update_radar Error: f{str(e)}")
    return jsonify({"status": "failed", "data": "failed"})  


@app.route('/api/weather/get/<start>/<end>', methods=['GET']) 
def get_all(start,end):   
    '''RETURNS ALL THE DATA FROM THE DATABASE THAT EXIST IN BETWEEN THE START AND END TIMESTAMPS'''
   
    if request.method == "GET":
        '''Add your code here to complete this route'''

        try:
            begin=escape(start)
            stop=escape(end)
            all=mongo.getAllInRange(begin,stop)
            print(all)
            if all:
                return jsonify({"status":"found","data": all}) 

        except Exception as e: 
            print(f"get_all error: f{str(e)}")    

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})


@app.route('/api/frequency/<variable>/<start>/<end>', methods=['GET']) 
def get_freq_distro(variable,start,end):   
    '''RETURNS FREQUENCY DISTRIBUTION FOR SPECIFIED VARIABLE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route''' 
        try:
            begin=escape(start)
            stop=escape(end)
            vary=escape(variable)
            frequency=mongo.frequencyDistro(vary,begin,stop)
            if frequency:
                return jsonify({"status":"found","data": frequency}) 

        except Exception as e: 
            print(f"get_freq_distro error: f{str(e)}")        

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})

@app.route('/api/mmar/temperature/<start>/<end>', methods=['GET']) 
def get_temperature_mmar(start,end):   
    '''RETURNS MIN, MAX, AVG AND RANGE FOR TEMPERATURE. THAT FALLS WITHIN THE START AND END DATE RANGE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route'''
        try:
            begin=escape(start)
            stop=escape(end)
            temp_mmar=mongo.temperatureMMAR(begin,stop)
            if temp_mmar:
                return jsonify({"status":"found","data": temp_mmar}) 

        except Exception as e: 
            print(f"get_temperature_mmar error: f{str(e)}")    


    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})





@app.route('/api/mmar/humidity/<start>/<end>', methods=['GET']) 
def get_humidity_mmar(start,end):   
    '''RETURNS MIN, MAX, AVG AND RANGE FOR HUMIDITY. THAT FALLS WITHIN THE START AND END DATE RANGE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route'''
        try:
            begin=escape(start)
            stop=escape(end)
            humid_mmar=mongo.humidityMMAR(begin,stop)
            if humid_mmar:
                return jsonify({"status":"found","data": humid_mmar}) 

        except Exception as e: 
            print(f"get_hummidity_mmar error: f{str(e)}")    

        

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})

@app.route('/api/mmar/pressure/<start>/<end>', methods=['GET']) 
def get_pressure_mmar(start,end):   
    '''RETURNS MIN, MAX, AVG AND RANGE FOR HUMIDITY. THAT FALLS WITHIN THE START AND END DATE RANGE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route'''
        try:
            begin=escape(start)
            stop=escape(end)
            pressure_mmar=mongo.pressureMMAR(begin,stop)
            if pressure_mmar:
                return jsonify({"status":"found","data": pressure_mmar}) 

        except Exception as e: 
            print(f"get_pressure_mmar error: f{str(e)}")    

        

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})

@app.route('/api/mmar/altitude/<start>/<end>', methods=['GET']) 
def get_altitude_mmar(start,end):   
    '''RETURNS MIN, MAX, AVG AND RANGE FOR HUMIDITY. THAT FALLS WITHIN THE START AND END DATE RANGE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route'''
        try:
            begin=escape(start)
            stop=escape(end)
            altitude_mmar=mongo.altitudeMMAR(begin,stop)
            if altitude_mmar:
                return jsonify({"status":"found","data": altitude_mmar}) 

        except Exception as e: 
            print(f"get_altitude_mmar error: f{str(e)}")    

        

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})

@app.route('/api/mmar/moisture/<start>/<end>', methods=['GET']) 
def get_moisture_mmar(start,end):   
    '''RETURNS MIN, MAX, AVG AND RANGE FOR HUMIDITY. THAT FALLS WITHIN THE START AND END DATE RANGE'''
   
    if request.method == "GET": 
        '''Add your code here to complete this route'''
        try:
            begin=escape(start)
            stop=escape(end)
            moisture_mmar=mongo.moistureMMAR(begin,stop)
            if moisture_mmar:
                return jsonify({"status":"found","data": moisture_mmar}) 

        except Exception as e: 
            print(f"get_moisture_mmar error: f{str(e)}")    

        

    # FILE DATA NOT EXIST
    return jsonify({"status":"not found","data":[]})

@app.route('/api/file/get/<filename>', methods=['GET']) 
def get_images(filename):   
    '''Returns requested file from uploads folder'''
   
    if request.method == "GET":
        directory   = join( getcwd(), Config.UPLOADS_FOLDER) 
        filePath    = join( getcwd(), Config.UPLOADS_FOLDER, filename) 

        # RETURN FILE IF IT EXISTS IN FOLDER
        if exists(filePath):        
            return send_from_directory(directory, filename)
        
        # FILE DOES NOT EXIST
        return jsonify({"status":"file not found"}), 404
















@app.route('/api/file/upload',methods=["POST"])  
def upload():
    '''Saves a file to the uploads folder'''
    
    if request.method == "POST": 
        file     = request.files['file']
        filename = secure_filename(file.filename)
        file.save(join(getcwd(),Config.UPLOADS_FOLDER , filename))
        return jsonify({"status":"File upload successful", "filename":f"{filename}" })

 


###############################################################
# The functions below should be applicable to all Flask apps. #
###############################################################


@app.route('/<file_name>.txt')
def send_text_file(file_name):
    """Send your static text file."""
    file_dot_text = file_name + '.txt'
    return app.send_static_file(file_dot_text)

@app.after_request
def add_header(response):
    """
    Add headers to both force latest IE rendering engine or Chrome Frame,
    and also tell the browser not to cache the rendered page. If we wanted
    to we could change max-age to 600 seconds which would be 10 minutes.
    """
    response.headers['X-UA-Compatible'] = 'IE=Edge,chrome=1'
    response.headers['Cache-Control'] = 'public, max-age=0'
    return response

@app.errorhandler(405)
def page_not_found(error):
    """Custom 404 page."""    
    return jsonify({"status": 404}), 404



