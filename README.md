# Supermarket-Management-System
 C++ OOP Project

## OS
Windows
## Environment
Dev C++ & Visual Studio

### Module Division
*The functions of each class and their relationship.*

Class Supermarket

    Member Object: Cash, Goods, just to name a few.
    Name: XMUMarket 
    Cash: 100

Class Goods	

    ·Includes name of the good, its production_date, its price and its quantity left.
    [Implemented by virtual function.] 
    Subclasses includes:
    ·Class DailyGoods 
    ·Class Food
    Includes guarantee_period( day ). 
    ·Class Electrical_Appliance
    Includes its color and maintenance_period. 

Class Order

    ·Includes the date of the order, lists of goods and relevant information.
    After each order is completed, the order information should be printed on the screen and saved locally in txt.
    Subclasses includes:
    ·Class out  decrease in numbers of goods and increase in revenue.
    ·Class in     the opposite.
    Includes the corresponding ID number and the reason for returning. 

*The function of each part of the program.*

    input()；menu();
    Inside menu()：
        case 1:sell();
            void Selling_substract(int choice)
        case 2:return_fun();
            void Return_add(int choice) 
        case 3:display();
            -> display(0);display(1);display(2);
        case 4:revenue_fun(); 
        case 5:output(); 

*txt File*

    market_in.txt  
    return_out.txt  
    order_out.txt  
    market_out.txt  

### C++ 
Friend
```c
    friend istream & operator>>(istream & in,Goods & A);
    friend ostream & operator<<(ostream & out, Goods & A);
    friend Goods operator + (Goods& g1,const Goods& g2);
    friend Goods operator - (Goods& g1,const Goods& g2);
    friend Goods operator = (Goods& g1,const Goods& g2);
    friend Goods operator * (int n, const Goods& g2);
```
(Pure) Virtual Function

    Using virtual int get_type() to classify the type of the child.
```c
    virtual int get_type()=0; //0 Daily  //1 Food  //2 EAppliance
```
Dynamic Binding
```c
    virtual int get_type()=0; //0 Daily  //1 Food  //2 EAppliance
 ```   
Operator Overloading
```c
    friend Goods operator + (Goods& g1,const Goods& g2);
    friend Goods operator - (Goods& g1,const Goods& g2);
    friend Goods operator * (int n, const Goods& g2);
    friend Goods operator = (Goods& g1,const Goods& g2);
``` 
### Interface
Initialization
![Initialization](Photo/Initialization.png)

Menu
![Menu](Photo/Menu.png)

Sell
![Sell1](Photo/Sell1.png)
![Sell2](Photo/Sell2.png)

Order
![Order](Photo/Order.png)
![Order-txt](Photo/Order-txt.png)

Display
![Display](Photo/Display.png)

Return
![Return](Photo/Return.png)
![Return-out](Photo/Return-out.png)

Revenue
![Revenue](Photo/Revenue.png)

Save
![Save](Photo/Save.png)
![Save-txt](Photo/Save-txt.png)
