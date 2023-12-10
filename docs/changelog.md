# Changelog

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