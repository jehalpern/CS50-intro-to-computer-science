# GitHub Card Lightning Web Component
#### Video Demo:  <https://www.youtube.com/watch?v=lQVr4l5VYSw>
#### Description: Salesforce is a customer relationship management (CRM) platform. It can track and process data at a massive scale. It accepts Javascript, html, Apex, CSS, SOQL and XML.


I created a custom lightning web component that renders a card displaying GitHub user information. I created records in the database with extra users and a custom field that contains the user’s GitHub username. The component has a search function that takes in the full name of a salesforce user in the database, queries the records and returns the GitHub user name, then passes the user name to an external api call that returns a json with their user info. It takes a few of the key value pairs and displays them in a card including their profile photo, number of followers
And member start date.


The database query is also an api call, but it is a different kind. It’s done through a specific process called a wire service. Any query made on a salesforce database must be done through a wire service call with a SOQL formatted query.

The html file displays the returned data in a formatted display. It utilizes the template tag which takes directives and can execute things like loops and conditional statements.

The XML file directs how the different code files get deployed and to what parts of the platform.

The javascript file imports functionality and constant variables. It also contains the variables that eventually get rendered in the html file. Under that there are functions to handle clicks and input value changes. It also has two api calls. The first one is a wire service that calls an apex class I created. It takes the full name that was entered into the search, then returns the github username stored in the database. The second api uses a rest api callout to contact the github api and returns a json then parses the information and stores it into a series of variables that gets rendered by the html file.

The apex class that gets called from the wire service call, takes the full name, uses it to execute a SOQL query on the database, and returns a List<User> which is an array of objects. SOQL is essentially SQL but optimized for the salesforce platform.

APEX is an object oriented programming language that is similar in syntax to Java. It is also developed by oracle. Oracle is also the database service provider for salesforce.

The design of the the Component could likely be improved through the use of life cycle hooks and async functions. There are functions that can be used to run process and functions asynchronously. This is really important when executing multiple api calls in conjunction with other functions. The program is also executed in several life cycle hooks functions can be called strategically using built in items such as connected call back ().

It is also possible to use declarative development techniques in place of programatic techniques to accomplish the different tasks in component. Developing functionality on the salesforce platform using declarative practices is more important than programatic. Declarative development involves point and click as well as drag and drop functionality. This approach os preferential because everything is configured to work best with salesforce. Custom components can make too many server calls, slowing the system down and causing excessive tech debt.
