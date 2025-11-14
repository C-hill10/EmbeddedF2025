#This is a basic script to host a webpage at the IP specified
# By the 'IP_Address' variable

# Import library to create webserver to host webpage
from flask import Flask, render_template
from flask import Flask, render_template, Response,redirect,request, url_for
import itertools
import time
app = Flask(__name__)



#Find the IP Address of your device
#Use the 'ifconfig' terminal command, the address should be in the format  "XX.XXX.XXX.XXX"
#IP_Address = '10.227.25.223'
IP_Address = '10.227.29.4'
PORT = 8080
#Connect the *.html page to the server and run as the default page


@app.route('/')
def index():
    if request.headers.get('accept') == 'text/event-stream':
        def events():
            for i, c in enumerate(itertools.cycle('\|/-')):

                # the following codes send the random sensor status to the webpage. Finsh the parse_data.js code
                yield "data: %s\n\n" % ('b0c0d0')
                time.sleep(1)
                yield "data: %s\n\n" % ('b1c1d1')
                time.sleep(1)
                yield "data: %s\n\n" % ('b2c2d2')
                time.sleep(1)
                yield "data: %s\n\n" % ('b3c3d3')
                time.sleep(1)
                yield "data: %s\n\n" % ('b4c4d0')
                time.sleep(1)
                yield "data: %s\n\n" % ('b5c5d1')
                time.sleep(1)
                
        return Response(events(), content_type='text/event-stream')
    return render_template('FinalEXE2b.html')



@app.route('/UpFunction')
def UpFunction():
    print('In UpFunction')
    return "Nothing"

# define the rest of the functions to handle the left, right, down and stop buttons (4 functions)
@app.route('/LeftFunction')
def LeftFunction():
    print('In LeftFunction')
    return "Nothing"
@app.route('/RightFunction')
def RightFunction():
    print('In RightFunction')
    return "Nothing"
@app.route('/StopFunction')
def StopFunction():
    print('In StopFunction')
    return "Nothing"
@app.route('/DownFunction')
def DownFunction():
    print('In DownFunction')
    return "Nothing"


    

#Start the server
if __name__ == "__main__":
    app.run(debug=True, host=IP_Address, port=PORT, use_reloader=False)
