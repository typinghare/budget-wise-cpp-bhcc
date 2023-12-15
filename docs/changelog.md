# Changelog

> Changelogs are written and maintained by James Chan. **Grammarly** is used to correct grammatical problems, and **ChatGPT** is used to improve sentences. 

## Nov 27  to Dec 3

* Established the foundational framework and directory structure for the application, providing a robust and organized foundation.
* Implemented a comprehensive user authentication system, featuring seamless functionality for user login, sign-up, and password reset.
* Implemented essential password utility functions, including robust encryption techniques for storing passwords securely. The system ensures the integrity of user identification by employing advanced methods for password validation against encrypted strings.
* Developed a user repository class with full CRUD (Create, Read, Update, Delete) capabilities, enabling efficient management of user data within the application. This foundational class sets the stage for the integration of additional repositories in upcoming updates.
* Implemented the `LocalUser` class to handle user pointers. The class triggers the login window when the pointer is null, prompting the user to log in. Upon successful login, the `LocalUser` securely stores the user pointer for application access.

## Dec 4 to Dec 7

* Added repositories and essential methods for all entities.
* Added category window and subcategory window, which allow users to manage their categories and subcategories. Users can retrieve, add, update, and delete categories and subcategories.
* Developed a utility class `TimeUtil`, which provides `setTimeout` and `setInterval` methods. Developers can leverage these two methods to schedule delay events and periodic events.
* Updated `WindowUtil`. Renamed the `navigate` method to the `jump` method. Now when jumping from one window to another, a smooth animation will be presented.
* Added `createConfirmationBox` method to `WindowUtil`. Developers can create a seamless confirmation message box using this method.

## Dec 8 to Dec 10

* Revamped the directory structure for improved clarity and organization.
* Implemented and extended the subcategory window functionality. Users can now effortlessly add, update, and delete subcategories directly within the window. Additionally, a convenient feature allows users to double-click on a category in the main window, instantly navigating to the subcategory window. When this occurs, the subcategory window's table is dynamically filtered to display only the subcategories associated with the selected category, enhancing user efficiency and focus.

## Dec 12 to Dec 14

* Introducing the Records Window, a user-friendly interface that showcases all records within a specific category. This addition empowers users with enhanced control over their transactions.
* Implemented a logout function accessible via the menu bar. Users can seamlessly log out with a simple click, ensuring a secure and convenient experience.
* Resolved issues related to signing up and resetting password procedures, enhancing the overall reliability and smooth functioning of the application.
* Unveiling the View Window, offering users an insightful visual representation of their data through interactive charts. Users can apply filters to explore specific categories and subcategories, enabling a more detailed analysis.
* Streamlined data management by implementing a feature that automatically deletes subcategories when their parent category is removed. Additionally, associated records will be seamlessly deleted when deleting the corresponding category or subcategory, ensuring a tidy and efficient data structure.
* Users now have the flexibility to create transactions without the constraint of selecting a category.