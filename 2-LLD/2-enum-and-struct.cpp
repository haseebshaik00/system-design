#include<bits/stdc++.h>
#include<iostream>
using namespace std;

enum class OrderStatus{
    PLACED,
    CONFIRMED,
    SHIPPED,
    DELIVERED,
    CANCELLED
};

string getOrderStatus(OrderStatus &status){
    switch(status){
        case OrderStatus::PLACED: return "Placed";
        case OrderStatus::CONFIRMED: return "Confirmed";
        case OrderStatus::SHIPPED: return "Shipped";
        case OrderStatus::DELIVERED: return "Delivered";
        case OrderStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}

struct PaymentMethod {
    string name;
    double feesPercent;

    static const PaymentMethod CREDIT_CARD;
    static const PaymentMethod DEBIT_CARD;
    static const PaymentMethod UPI;
    static const PaymentMethod NET_BANKING;
};

const PaymentMethod PaymentMethod::CREDIT_CARD{"CREDIT_CARD", 3.5};
const PaymentMethod PaymentMethod::DEBIT_CARD{"DEBIT_CARD", 2.5};
const PaymentMethod PaymentMethod::UPI{"UPI", 0.0};
const PaymentMethod PaymentMethod::NET_BANKING{"NET_BANKING",0.0};

class Order{
public:
    string orderId;
    OrderStatus status;
    PaymentMethod paymentMethod;
    double totalAmount;

    Order(string orderId, PaymentMethod paymentMethod, double totalAmount):
    orderId(orderId), paymentMethod(paymentMethod), totalAmount(totalAmount), status(OrderStatus::PLACED){
        if(totalAmount <= 0)
            throw invalid_argument("Total amount must be positive!");
    }

    bool advanceOrderStatus(){
        switch(status){
            case OrderStatus::PLACED: status = OrderStatus::CONFIRMED; return true;
            case OrderStatus::CONFIRMED: status = OrderStatus::SHIPPED; return true;
            case OrderStatus::SHIPPED: status = OrderStatus::DELIVERED; return true;
            default: return false;
        }
    }

    bool cancelOrder(){
        if(status == OrderStatus::PLACED || status == OrderStatus::CONFIRMED){
            status = OrderStatus::CANCELLED;
            return true;
        }
        return false;
    }

    double getTotalAmount(){
        return totalAmount*(1+paymentMethod.feesPercent/100);
    }

    void displayOrderDetails(){
       cout<<"--------------------------------"<<endl;
       cout<<"Order Details"<<endl;
       cout<<"--------------------------------"<<endl;
        cout<<"Order ID: "<<orderId<<endl;
        cout<<"Order Status: "<<getOrderStatus(status)<<endl;
        cout<<"Payment Method: "<<paymentMethod.name<<endl;
        cout<<"Total Amount: "<<getTotalAmount()<<endl;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Order order("123456", PaymentMethod::CREDIT_CARD, 1000);
    order.displayOrderDetails();
    order.advanceOrderStatus();
    order.displayOrderDetails();
    order.cancelOrder();
    order.displayOrderDetails();
    return 0;
}