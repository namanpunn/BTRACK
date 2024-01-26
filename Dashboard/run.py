import os
from flask_migrate import Migrate
from flask_minify  import Minify
from sys import exit
try:
    #To implement API (At a later stage)
    from api_generator.commands import gen_api
    API_IMPORT_SUCCESS = True
except:
    API_IMPORT_SUCCESS = False
    pass

from apps.config import config_dict
from apps import create_app, db

# Till the app is ready for deployment, this should be kept True
DEBUGGING = True

# Setting the configuration mode to DEBUGGING or production.
get_config_mode = 'Debug' if DEBUGGING else 'Production'


try:
    # Load the configuration using the default values
    app_config = config_dict[get_config_mode.capitalize()]

except KeyError:
    exit('Error: Invalid <config_mode>. Expected values [DEBUGGING, Production] ')

app = create_app(app_config)

Migrate(app, db)

if not DEBUGGING:
    Minify(app=app, html=True, js=False, cssless=False)
    
if DEBUGGING:
    app.logger.info('DEBUGGING        = ' + str(DEBUGGING)             )
    app.logger.info('Page Compression = ' + 'FALSE' if DEBUGGING else 'TRUE' )
    app.logger.info('DBMS             = ' + app_config.SQLALCHEMY_DATABASE_URI)
    app.logger.info('ASSETS_ROOT      = ' + app_config.ASSETS_ROOT )

if API_IMPORT_SUCCESS:
    for command in [gen_api, ]:
        app.cli.add_command(command)

# Starting the Server
if __name__ == "__main__":
    app.run("127.0.0.1", port=5000, debug=DEBUGGING)