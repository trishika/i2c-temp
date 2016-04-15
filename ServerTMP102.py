#!/usr/bin/env python2
# -*- encoding: utf-8 -*-

"""
    Custom bridge between DTH11 sensor and domoticz
"""

try:
    import sys, time, threading
    import urllib2
    import time
    import BaseHTTPServer
    import subprocess
except ImportError as error:
    print 'ImportError: ', str(error)
    exit(1)

host="0.0.0.0"
port=9999
idx=1
pin=4

class MyHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/json")
        s.end_headers()

    def do_GET(s):
        """Respond to a GET request."""
        s.send_response(200)
        s.send_header("Content-type", "text/json")
        s.end_headers()

        temperature = subprocess.Popen(["/usr/local/bin/tmp102"], stdout=subprocess.PIPE).communicate()[0]

        if temperature:
            s.wfile.write(
"""
  {
    "temperature": %s,
    "humidity": 0
  }
""" % (temperature))


if __name__ == '__main__':
    server_class = BaseHTTPServer.HTTPServer
    httpd = server_class((host, port), MyHandler)
    print time.asctime(), "Server Starts - %s:%s" % (host, port)

    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
