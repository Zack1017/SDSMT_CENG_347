# Laboratory 0

## Getting Started with PlatformIO IDE

### Step 1: Install Visual Studio Code
Go to the following link (https://code.visualstudio.com/#alt-downloads) and download the version pertaining to your operating system.

### Step 2: Installing Extensions
For this class we will be coding mostly in C with some AVR assembly, so if we want VS Code to give us syntax highlighting, we will need to add the requisite extensions. 

Click on the squares on the left-hand panel to bring up the extensions. From there go ahead and search for “C” or “C++”and install the extension from Microsoft by clicking the install button. 

![Figure 1](/Lab00/assets/images/Figure1.png)

Search again for “AVR Assembly” and install the one from rockcat.

![Figure 2](/Lab00/assets/images/Figure2.png)


If you clear the search field, it should show your installed extensions and you should see the two language support extensions now installed.

![Figure 3](/Lab00/assets/images/Figure3.png)

Now we will install PlatformIO, which is also conveniently an extension. Search for it and install it from the Extensions Marketplace.

![Figure 4](/Lab00/assets/images/Figure4.png)

You may be prompted to reload VS Code, if so, please do so.

### Step 3: Creating a Project
Now we can begin creating a project with PlatformIO. You should have a new icon on your left panel for the extension. Select it from the right and click on “Open” in the menu. This will bring up the PlatformIO home page where you can create and open projects. Since we have none yet, select “New Project”.

![Figure 5](/Lab00/assets/images/Figure5.png)

Fill out the fields for the new project wizard. Enter a name for the project and search/select the board to be “ATMega2560”. Additionally, if you want to store this project in a certain location (which I recommend) uncheck the box using default location and find a file path that suits you. The project will be created in this directory and will have a subdirectory with the same name as the project.

![Figure 6](/Lab00/assets/images/Figure6.png)


Now we have an empty project with a source file in the src folder. Clicking on the files on the left bar brings up the explorer, and we can see our source file in here.

![Figure 7](/Lab00/assets/images/Figure7.png)


### Step 4: Building and Uploading to the Board
Write the code below in your main.cpp any try to build it.

When you have the code, go ahead and select the PlatformIO icon on the left panel. From here you can select Build, Upload, Monitor, and Upload and Monitor. Selecting upload will also build the program before flashing. Monitor and Upload and Monitor will become relevant when we begin with Serial interfacing.

![Figure 8](/Lab00/assets/images/Figure8.png)


Once you are done with these steps, monitor the board and put its screenshot in your report.