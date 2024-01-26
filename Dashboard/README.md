Instructions to use the Application
=

To successfully launch and utilize the dashboard, please follow the steps outlined below:

Using Virtual Environment:
-

1. **Python Installation:**

    Ensure that Python is correctly installed on your system and added to the PATH variable. 
    If Python is not installed, you can download it from the official website: 
    [https://www.python.org/downloads/](https://www.python.org/downloads/)

2. **Set up the virtual environment**
    
    Open a command prompt in the project directory and execute the following command:
    
    `venv\scripts\Activate.bat`
    
    Or, if using powershell, execute:

    `venv\scripts\Activate.ps1`

3. **Start the Dashboard**

    After successfully installing the dependencies, launch the dashboard by executing the following command 
    `python run.py`.

    This command will initiate the dashboard application and host it [here](https://127.0.0.1) 

Without using virtual environment 
-

If you don't have that much confidence in using Virtual Environments, below guide is for you
1. **Python Installation:**

    Ensure that Python is correctly installed on your system and added to the PATH variable. 
    If Python is not installed, you can download it from the official website: 
    [python.org/downloads/](https://www.python.org/downloads/)

2. **Command Prompt:**
    
    Open a command prompt in the current directory where the dashboard files are located.

3. **Install Dependencies:**
    
    Execute the following command to install the required dependencies using the provided 'requirements.txt' file 
    
    `pip install -r "requirements.txt"`

4. **Start the Dashboard** 

    After successfully installing the dependencies, launch the dashboard by executing the following command 
    `python run.py`.

    This command will initiate the dashboard application and host it [here](https://127.0.0.1) 
