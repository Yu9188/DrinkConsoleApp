#include "DrinkConsoleApp.h"

int main()
{
	vector<DrinkItem> drinks;
	vector<OrderItem> order;

	AddNewDrink(drinks);

	DisplayDrinkMenu(drinks);

	OrderDrink(order, drinks);

	CalculateSalePrice(order, drinks);

	return 0;
}

void AddNewDrink(vector<DrinkItem>& drinks)
{
	drinks.push_back(DrinkItem("紅茶", "大杯", 60));
	drinks.push_back(DrinkItem("紅茶", "小杯", 40));
	drinks.push_back(DrinkItem("綠茶", "大杯", 60));
	drinks.push_back(DrinkItem("綠茶", "小杯", 40));
	drinks.push_back(DrinkItem("咖啡", "大杯", 80));
	drinks.push_back(DrinkItem("咖啡", "小杯", 50));
	drinks.push_back(DrinkItem("可樂", "大杯", 30));
	drinks.push_back(DrinkItem("可樂", "小杯", 20));
}

void DisplayDrinkMenu(vector<DrinkItem>& drinks) {
	cout << setw(4) << "編號" << setw(10) << "飲料名稱" << setw(10) << "大小" << setw(10) << "售價" << endl;
	cout << "--------------------------------------" << endl;
	int i = 1;
	for (int j = 0; j < drinks.size(); j++) {
		cout << setw(4) << i;
		drinks[j].displayItem();
		i++;
	}
	cout << "--------------------------------------" << endl;
	cout << "總共有" << drinks.size() << "個飲料品項" << endl;
}

void OrderDrink(vector<OrderItem>& order, vector<DrinkItem>& drinks) {
	int index;
	int qty;
	char ans = 'Y';

	do {
		cout << "請輸入要訂購的飲料編號： ";
		cin >> index;
		cout << "請輸入要訂購的飲料數量： ";
		cin >> qty;

		if (index < 1 || index>drinks.size()) {
			cout << "輸入飲料品項編號錯誤，請重新輸入！" << endl;
		}
		else if (qty < 1) {
			cout << "輸入飲料數量錯誤，請重新輸入！" << endl;
		}
		else {
			OrderItem orderitem = OrderItem(index, qty);
			order.push_back(orderitem);
			orderitem.displayOrderItem(drinks);
			cout << "是否繼續點餐？(Y或y鍵繼續訂餐)";
			cin >> ans;
		}
	} while (ans == 'Y' || ans == 'y');
}

void CalculateSalePrice(vector<OrderItem>& order, vector<DrinkItem>& drinks) {
	int takeIn = 1;
	cout << "請問是內用還是外帶？(1:內用 2:外帶): ";
	cin >> takeIn;
	string messageTakeIn = (takeIn == 1) ? "內用" : "外帶";

	int totalPrice = 0;
	int salePrice = 0;
	string messagePrice = "";
	cout << "---------------------------------" << endl;
	cout << "您所點的飲料如下：" << endl;
	cout << "---------------------------------" << endl;
	for (OrderItem orderitem : order) {
		orderitem.displayOrderItem(drinks);
		DrinkItem drinkitem = drinks[orderitem.getIndex() - 1];
		totalPrice += drinkitem.getPrice() * orderitem.getQuantity();
	}

	if (totalPrice >= 500) {
		salePrice = totalPrice * 0.8;
		messagePrice = "訂購滿500元以上者8折";
	}
	else if (totalPrice >= 300) {
		salePrice = totalPrice * 0.85;
		messagePrice = "訂購滿300元以上者85折";
	}
	else if (totalPrice >= 200) {
		salePrice = totalPrice * 0.9;
		messagePrice = "訂購滿200元以上者9折";
	}
	else {
		salePrice = totalPrice;
		messagePrice = "訂購未滿200元不打折";
	}

	cout << "---------------------------------" << endl;
	cout << "訂購方式： " << messageTakeIn << endl;
	cout << "總金額： " << totalPrice << endl;
	cout << messagePrice << endl;
	cout << "售價： " << salePrice << endl;
	cout << "---------------------------------" << endl;
}