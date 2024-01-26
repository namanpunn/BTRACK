from apps.home import blueprint
from flask import render_template, request
from flask_login import login_required
from jinja2 import TemplateNotFound

from apps.config import API_GENERATOR

gps_data = {}

@blueprint.post('/updategps')
def updateGPS():
    global gps_data
    gps_data = request.json
    print("RECEIVED DATA!!! DATA= ", gps_data)
    return "GPS DATA RECEIVED", 200

@blueprint.route('/index')
@login_required
def index():
    return render_template('home/index.html', segment='index', API_GENERATOR=len(API_GENERATOR), gps_data=gps_data)

@blueprint.route('/<template>')
@login_required
def route_template(template):

    try:

        if not template.endswith('.html'):
            template += '.html'

        # Detect the current page
        segment = get_segment(request)

        # Serve the file (if exists) from app/templates/home/FILE.html
        return render_template("home/" + template, segment=segment, API_GENERATOR=len(API_GENERATOR))

    except TemplateNotFound:
        return render_template('home/page-404.html'), 404

    except:
        return render_template('home/page-500.html'), 500


# Helper - Extract current page name from request
def get_segment(request):

    try:

        segment = request.path.split('/')[-1]

        if segment == '':
            segment = 'index'

        return segment

    except:
        return None
