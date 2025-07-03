# 🍽️ Restaurant Menu Order System  
 A fully functional C++ terminal application that brings a restaurant ordering and billing experience right into your console.
  Designed with dynamic menu handling, real-time billing, and historical tracking—crafted for clarity, modularity, and learning!

---

## 📖 Overview  
The **Restaurant Menu Order System** is a personal console-based application developed entirely using C++.
 It provides a seamless and interactive user interface through the terminal, simulating a real-world restaurant's menu, order, and billing experience.
  This project was created to deepen hands-on understanding of C++ programming, particularly focusing on file handling, modular design, and user-centric logic flow.

---

## ✨ Core Features  

✅ **Show Menu**  
- Reads from `menu.txt` and presents the items in a formatted style.  

✅ **Add Item(Admin Mode)**  
- Add new dishes on the fly, with ID, name, and price inputs.  
- Uses a backup strategy (`temp_menu.txt`) to ensure file safety.

✅ **Take Order**  
- Accepts item selection via ID and desired quantity.  
- Verifies item availability from the live menu data.

✅ **Generate Bill**  
- Automatically calculates item total, adds a 5% tax, and includes a 10% discount if the order exceeds ₹1000.  
- Displays and saves a clean, timestamped receipt to `orders.txt`.

✅ **View Order History**  
- Displays a list of all previous orders with customer names and billing breakdowns.  
- Helps track transactions across sessions.

✅ **Search Item**  
- Users can search for items by partial name (case-sensitive).  
- Filters and presents matches in a readable format.

✅ **Interactive Menu-Driven Flow**  
- Easy-to-follow numbered menu options guide the user through the application.

---

## 🛠️ How It Works – Logic Flow  
1. User enters the application and selects actions from a numbered menu.  
2. Menu data is loaded from `menu.txt` and displayed dynamically.  
3. User can either order items, add new ones, or search the menu.  
4. When an order is placed, details are logged to `order.txt`.  
5. On generating a bill, the system:  
   - Calculates total  
   - Adds tax and discount  
   - Generates a bill with timestamp and customer name  
   - Appends it to `orders.txt`  
6. Session ends when the user selects the exit option.

---

## 🖼️ Screenshots  

![Screenshot 2025-07-03 200558](https://github.com/user-attachments/assets/3403d773-d0fa-4616-beb8-3f8576e2cdd4)
![Screenshot 2025-07-03 201110](https://github.com/user-attachments/assets/0477246a-a2ad-4828-85c9-25d751866ecf)
![Screenshot 2025-07-03 200735](https://github.com/user-attachments/assets/081e0427-404a-4903-83de-d497bf949eca)
