# Chamaecrista Sustainability System (CSS) - User Interface

# Folder Structure
This project is composed of the following folders:

![image](https://user-images.githubusercontent.com/33732521/203176087-10e15629-b0c6-4096-bdc8-76869c5ac0cf.png)


# Node Modules
The node_modules folder is a file that is actually ignored by git as it contains all of teh downloaded dependencies specified by the package.json and which are needed to render the user interface

# Public
The public folder contains the base html of the page which specifies values such as the web page's name. It also containes some base images such as backgrouns or favicons. 

# SRC
SRC, Source or src is the main project folder and contains all of the actual React.js code that runs our User Interface

![image](https://user-images.githubusercontent.com/33732521/203176986-8466d966-0cc7-4d3f-8f5a-c2d05758d1f6.png)

## __ _tests_ __

_example __tests__ folder_

![image](https://user-images.githubusercontent.com/33732521/203177954-8c7b9f7d-a20e-407b-84e2-a63feb7bccc6.png)

The first folder we see here is the `__test__` folder, which is actually repeated inside of each folder of src that contains a React.js component or page. Each of these `__test__` folders contain files with specifc JEST (Javascript Testing Framework) tests for the specifc components they represents. More on these tests briefly.

## _Components_

![image](https://user-images.githubusercontent.com/33732521/203178188-6050a8b1-33aa-403d-83a7-f91d47ad754c.png)

The `Components` folder contains all of the main React.js components that are used in order to form our different pages. These include the different buttons used, the tables, graphs, navbar, searches, among others which will be explored briefly.

-------------------------------------

### DataGraph Component

![image](https://user-images.githubusercontent.com/33732521/203181331-58523253-88e7-4136-9869-9ea2fa8c9fc2.png)

![image](https://user-images.githubusercontent.com/33732521/203181379-371edaa6-bb40-46cf-8d42-42a0df76097d.png)

The _DataGraph_ component contains the necessary code to render graphs in our React pages and it does so thanks to the chart.js library. It is a considered a child component of the _ViewGraphsPage_ and receives one value as props as a result of this:

@param `yVal` denotes what environmental data will be rendered as the Y axis in a graph with the _entryId_ as the X axis

-------------------------------------

### DataTable Component

![image](https://user-images.githubusercontent.com/33732521/203185138-91732117-6e0a-421f-b4e1-fe1c23babdaa.png)

![image](https://user-images.githubusercontent.com/33732521/203185160-bac0b850-6348-46e1-8fe0-ee914b2370ab.png)

![image](https://user-images.githubusercontent.com/33732521/203185209-83ab2e6c-cd7b-4958-93aa-8e1e04321a89.png)

The _DataTable_ component is the main feature of the CSS and it allows user to view the data present in the Environmental Data Table in real time. It loads in the data in sets of 12 pages at a time called pages, and the user has the ability to move in between these pages using the in built pagination  component that handles the movement between pages. 

--------------------------------------

### FilterSearch Component

![image](https://user-images.githubusercontent.com/33732521/203190013-67a5b480-9116-4dc1-8701-f0de54da97aa.png)

At the moment, _FilterSearch_ is a placeholder component for a more in depth filter feture that will be linked to the table

--------------------------------------

### Navbar Compoenent

![image](https://user-images.githubusercontent.com/33732521/203190320-98347540-104f-417c-8342-e187f52b70bb.png)

The _Navbar_ component is a simple component that is present throught all of the page sin this application and allows the user to return to the home page at any moment.

--------------------------------------

### PictureCard Component

![image](https://user-images.githubusercontent.com/33732521/203195339-a6a9a274-aab1-4337-85c4-ead97c01bf6c.png)

![image](https://user-images.githubusercontent.com/33732521/203195441-61961487-d477-4ac0-b444-9f0929827c74.png)

![image](https://user-images.githubusercontent.com/33732521/203195588-8553d478-60e1-44b8-9f27-c08d6ffa13f1.png)

The _PictureCard_ Component acts as the parent component of the _SingleCard_ and it serves the function of rendering 2 rows of 4 pictures each with pagination to navigate between all of the currently available pictures, two rows of 4 pictures at a time. This division makes the page less cluttered and offers readability to the user. It is very similar to the _DataTable_ Component.

--------------------------------------

### SingleCard Component

![image](https://user-images.githubusercontent.com/33732521/203197010-ea79e888-614d-4b65-b3a5-b863e1db0cdf.png)

The _SingleCard_ component is the child component of the the _PictureCard_ Component and is in charge of rendering individual cards with picture and classification data relating to it. It receives 6 prop values as a resul tof being a child component:

@param `src` denotes the image source URL and is responsible for showing the actual picture

@param `camNum` denotes the number of the camera that took the picture from 1 to 4

@param `id` denotes the id of the picture it is currently displaying so the user may refer to it anywhere else.

@param `classif_id` denotes the classification_id found in the Pictures table and originating from the Machine Learning Algorithm: 0 for Open, 1 for Closed, and Not Available for everything else

@param `classif_acc` denotes the accuracy or certanty the model returns for the classification_id mentioned above

@param `time` denotes the time in which the picture was taken in Unix Time


--------------------------------------

### Buttons

![image](https://user-images.githubusercontent.com/33732521/203197469-30d4e6e1-f696-41eb-b78e-bbab9be19dd2.png)

The `Components` folder contains another folder inside called `Buttons`, this folder contains all of the buttons, with their specifc use cases and values. All Buttons contained are similar, however they differ in what they do and what other components they call.

#### CalibrateMoistureButton

The _CalibrateMoistureButton_ is currently in development and undergoing optimization and code redundancy elimination and as such will not be displayed at the moment

#### ChangeLightLevelButton

![image](https://user-images.githubusercontent.com/33732521/203210036-54cef487-4a0a-455c-a314-310f41374e15.png)

![image](https://user-images.githubusercontent.com/33732521/203210074-5fe2242b-d29b-4bc3-ab76-0f59f0e29928.png)

The _ChangeLightLevelButton_ is responsible of allowing the user to input the light levels they wish the plant to have at the current moment. It features a modal that pops up and allows the user to use a slider to set each individual light level before submiting.

#### ExportAsCsvButton

![image](https://user-images.githubusercontent.com/33732521/203212844-544d0c0a-dc50-4332-9b62-41337719dd6c.png)

The _ExportAsCsvButton_ is a very simple button that takes care of formating the data obtained from the EnvironmentalData table in the DB and allows the user to save said data to their computer.

#### RetrainModelButton

The _RetrainModelButton_ is currently in the final stages of development and as such shall not be shown here

#### ViewAsGraph

![image](https://user-images.githubusercontent.com/33732521/203213104-31f19474-9aef-42ad-a4ab-3db12273d275.png)

The _ViewAsGraphButton_ is a very simple button whose sole purpose is to link to the _ViewAsGraphPage_
Page.

#### ViewCapturesButton

![image](https://user-images.githubusercontent.com/33732521/203213207-56d52c5d-fafe-4869-affc-204afedd8537.png)

The _ViewAsCapturesButton_'s fucntion is exactly the same as the  _ViewAsGraphButton_, however it instead links to the _ViewCapturesPage_.

#### WaterPlantButton

![image](https://user-images.githubusercontent.com/33732521/203213323-f59ddf6a-fb91-4de5-a69f-a4c55dc844af.png)

The _WaterPlantButton_ is the simplest of the command execution buttons, it's purpose is to send a POST request to the API with the string: "WaterPlant"

## _Pages_

![image](https://user-images.githubusercontent.com/33732521/203214046-40331d34-f74b-451a-b163-0d163e151a03.png)

The `Pages` folder contains the React components that act as "Pages" or in other words, collections of components that achieve a unified goal. In particular we have two pages present in this folder: 

-------------------------------------

### ViewCapturesPage

![image](https://user-images.githubusercontent.com/33732521/203214364-0fc4f7f3-d03a-4ae3-a760-182d67efc72e.png)

The _ViewCapturesPage_ is a simple page because it's components: _Navbar_ and _PictureCard_ do all the heavy lifting.

-------------------------------------

### ViewGraphsPage

![image](https://user-images.githubusercontent.com/33732521/203219388-073e0529-d245-4d47-8ed9-d7a2fe0bd240.png)

The _ViewGraphsPage_ contains three components, _Navbar_, An in built dropdown selector, and _DataGraph_ and it allows the user to select what variable they wish to see a graph of in relation to the entry Id.

## Resoruces

The `Resoruces` or resources folder is where any extra visual or audio content would go to be rendered or used by another component. At this moment it only contains a single svg file used by the `public` folder in rendering the base html.

## Styles 

![image](https://user-images.githubusercontent.com/33732521/203219968-02099d2f-948d-40dd-a4a8-46887d3017b4.png)

The `Styles` or styles folder contains all of the external css styling files for the components in the project.

## Util

The `Util` folder is a placeholder folder that will contai nany helper functions that may be used in the future such as: authentication help, web vitals reporting, among other.

## App.js

![image](https://user-images.githubusercontent.com/33732521/203220252-282cabeb-1bdc-4b48-9cf5-370a13cf864a.png)

The _App.js_ file is the launch point of our Web Application and asuch is the first page that is loaded up, It contains all of the navigation towards the other pages as well as a view at the EnviromentalData table and the command buttons. Aside from that, it is a standard React Page file.

## index.js

![image](https://user-images.githubusercontent.com/33732521/203220526-7cefffeb-20d8-4524-9546-2abcb46f4820.png)

The _index.js_ file is the equivalent of the `public` folders html base, but for React and javascript code. It contains a base off of which all other React components launch.

## package.json

![image](https://user-images.githubusercontent.com/33732521/203220732-f9d76d2e-44d0-4203-a2b8-ca4835d887eb.png)

The _package.json_ file is a standard dependency management file used for projects based off of node.js and it contains all of the dependencies the code needs to run.

-----------------------------------------------------------------------------

## The code featured is still being improved upon and may look different in a final version
