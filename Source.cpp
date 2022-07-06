#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <mysql.h>
#include <windows.h>  
using namespace std;

//start db connection
int qstate;
MYSQL* conn;
MYSQL_RES* res;
MYSQL_ROW row;
string UserID;

class db_response
{
public:
	static void ConnectionFunction()
	{
		conn = mysql_init(0);
		if (conn)
			cout << "Database Connected" << endl;
		else
			cout << "Failed To Connect!" << endl;

		conn = mysql_real_connect(conn, "localhost", "root", "", "workshop1db", 3306, NULL, 0);
		if (conn)
			cout << "Database Connected To MySql" << endl;
		else
			cout << "Failed To Connect!" << endl;
	}
};
//end db connection


void user(); //user module
void registerUser();
void loginUser();
void devmenu(); //developers only menu
void ownermenu();//owners menu
void addfeedback();
void getfeedback();
void inventory();//inventory module
void addInventory();
void updateInventory();
void afterupdateInv();
void deleteInventory();
void listInventory();
void searchInventory();
void audmenu();
void revenue();//revenue module
void step1UpdateRev();
void finalUpdateRev();
void report();//report module

int main()
{
	db_response::ConnectionFunction();
	system("cls");
	cout << "***************************************************************************"<<endl;
	cout << "*                                                                         *"<<endl;
	cout << "*                                                                         *" << endl;
	cout << "*                          "<< "GG GENERAL STORE" <<"                               *" << endl;
	cout << "*                     " << "INVENTORY MANAGEMENT SYSTEM" << "                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "*                                                                         *" << endl;
	cout << "***************************************************************************"<<endl<<endl;

	cout << "                     PRESS ENTER TO START THE SYSTEM";
	while ("ENTER")
	{
		if (_kbhit())
		{
			system("cls");
			user();
		}
	}
	return 0;
	
} 


void user()
{
	int response;
	system("cls");
	cout << "-----------------------USER MENU-----------------------" << endl;
	cout << "ACTIVITY CODE              ACTIVITY " << endl;
	cout << "    1                      REGISTER " << endl;
	cout << "    2                      LOGIN" << endl;
	cout << "    3                      EXIT" << endl;
	cout << "\nPLEASE ENTER THE ACTIVITY CODE >> "; 
	cin >> response;

	switch (response)
	{
		case(1):
			registerUser();
			break;
		case(2):
			loginUser();
			break;
		case(3):
			main();
			break;
		default:
			cout << "\nPLEASE ONLY ENTER THE AVAILABLE ACTIVITY CODE";
			_getch();
			user();

	}
}

void registerUser()
{
	system("cls");
	string user_name, user_email, user_password;
	cout<< "--------------REGISTER PAGE--------------" << endl;
	cout << "Enter Name: ";
	cin.ignore(1, '\n'); //include space
	getline(cin, user_name);
	cout << "Enter Email: "; //should be unique
	getline(cin, user_email);
	cout << "Enter Password: ";
	getline(cin, user_password);


	//check  yg sedia ada dlm database
	string checkUser_query = "select * from user where user_email = '" + user_email + "'";
	const char* cu = checkUser_query.c_str(); //compare input dgn data dlm database
	qstate = mysql_query(conn, cu); //execute query

	if (!qstate)//boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) //email exist
		{
		  
			cout << "\nEMAIL IS ALREADY EXIST. PRESS ENTER TO TRY AGAIN...";
			_getch();
			registerUser();
		}
		else
		{
			string insertUser_query = "insert into user (user_name, user_email , user_password) values ('" + user_name + "', '" + user_email + "', '" + user_password + "')";
			const char* q = insertUser_query.c_str(); //convert
			qstate = mysql_query(conn, q); //execute

			if (!qstate) //query boleh jalan
			{
			
				cout << endl << "YOU HAVE BEEN REGISTERED. PRESS ENTER TO CONTINUE...";
				_getch();
				ownermenu();
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

//ada update: error utk role code
void loginUser()
{
	system("cls");
	string user_email;
	string user_password;
	char c;
	int role = 0;


	cout << "--------------LOGIN PAGE--------------" << endl;
	cout << "\nDeveloper(1) or Owner/User (2) : ";
	cin >> role;


	if (role == 1)
	{
		devmenu();

	}
	else if (role == 2)
	{

		cout << endl;
	    cout << "Email : ";
		cin >> user_email;
		cout << "Password : ";
		char ch;
		while ((ch = _getch()) != 13)
		{
		user_password += ch;
		cout << '*';
		}

		

		//check username dgn password dlm database
		string checkUser_query = "select * from user where user_email = '" + user_email + "' and user_password = '" + user_password + "'";
		const char* cu = checkUser_query.c_str();//convert
		qstate = mysql_query(conn, cu);//execute

		if (!qstate)//query
		{
			res = mysql_store_result(conn);
			if (res->row_count == 1)//if user ada dlm table
			{
				while (row = mysql_fetch_row(res))//selagi user ada dlm table
				ownermenu();
			}
			else
			{
			
				char c;
				cout << "\n\nInvalid username or password. Want to try again? (y/n): ";
				cin >> c;
				if (c == 'y' || c == 'Y')
					loginUser();
				else
					main();
			}
		}
		else
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;

	}
	else
	{
		cout << "\nENTER AVAILABLE ROLE NUMBER ONLY.";
		_getch();
		loginUser();
	}
}


void devmenu()
{
	system("cls");
	int route;

	cout << "--------------DEV MENU--------------" << endl;
	cout << "\nACTIVITY CODE              ACTIVITY " << endl;
	cout << "    1             GET FEEDBACK FROM USER " << endl;
	cout << "    2             EXIT " << endl;
	cout << "\nPLEASE ENTER THE ACTIVITY CODE HERE >> ";
	cin >> route;

		if (route == 1)
		{
			getfeedback();
		}
		else if (route == 2)
		{
			main();
		}
		else
		{
			cout << "PLEASE ENTER THE AVAILABLE ACTIVITY CODE ONLY, THANKS";
			_getch();
			devmenu();
		}
}

void ownermenu()
{
	system("cls");
	int route;

	cout << "-----------------------OWNER MENU-----------------------"<<endl;
	cout << "\nACTIVITY CODE              ACTIVITY " << endl;
	cout << "    1             ADD/UPDATE/DELETE/LIST/SEARCH INVENTORY " << endl;
	cout << "    2             DISPLAY PROFIT/LOSS STATEMENT " << endl;
	cout << "    3             ADD FEEDBACK REGARDING THE SYSTEM " << endl;
	cout << "    4             EXIT " << endl;
	cout << "\nPLEASE ENTER THE ACTIVITY CODE HERE >> ";
	cin >> route;

	if (route == 1)
	{
		inventory();
	}
	else if (route == 2)
	{
		report();
	}
	else if (route == 3)
	{
		addfeedback();
	}
	else if (route == 4)
	{
		main();
	}
	else
	{
		cout << "PLEASE ENTER THE AVAILABLE ACTIVITY CODE ONLY, THANKS";
		_getch();
		system("cls");
		ownermenu();
	}
}

void addfeedback()
{
	system("cls");
	string feedback_rating, feedback_desc, feedback_improve, chose, user_id;

	cout << "--------------ADD FEEDBACK PAGE--------------" << endl;
	cout << "\nUSER ID (1-> THE OWNER, 2->TEST ACCOUNT): ";
	cin.ignore(1, '\n');
	getline(cin, user_id);
	cout << "\nRATING FOR THIS SYSTEM (1-> THE WORST, 10->THE BEST): ";
	getline(cin, feedback_rating);
	cout << "\nDESCRIPTION FOR THE RATING GIVEN: ";
	getline(cin, feedback_desc);
	cout << "\nPROPOSED IMPROVEMENT FOR THIS SYSTEM: ";
	getline(cin, feedback_improve);

	//compare dgn apa yg dlm database
	string insertFeed_query = "insert into feedback (user_id, feedback_rating,feedback_desc,feedback_improve) values ('" + user_id + "','" + feedback_rating + "','" + feedback_desc + "','" + feedback_improve + "')";
	const char* q = insertFeed_query.c_str();//convert sebab c++ kena tukar ke char
	qstate = mysql_query(conn, q);//execute

	//YYYY-MM-DD//default date format

	if (!qstate) //query boleh jalan
	{
		cout << endl << "\nFEEDBACK SUCCESSFULLY ADDED IN THE DATABASE!" << endl;

	}
	else //query tak boleh jalan
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		_getch();

	}
	do
	{
		cout << "Press a to add another feedback, f to finish the operation: ";
		cin >> chose;
		if (chose == "a")
		{
			addfeedback();
		}
		else if (chose == "f")
		{
			ownermenu();
		}
	} while (chose != "a" && chose != "f");





}

void getfeedback()
{
	string chose;
	system("cls");
	cout << "\t\t\t\t--------------GET FEEDBACK--------------" << endl;

	qstate = mysql_query(conn, "select user_id, feedback_rating, feedback_desc, feedback_improve from feedback");

	if (!qstate)
	{
		//setw = set width
		cout << setw(11) << "User ID" << setw(20) << "Rating" << setw(50) << "Description" << setw(50) << "Proposed Improvement" << endl;

		//body table
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) //fetch every row untill the end of data
		{
			cout << setw(8) << row[0] << setw(20) << row[1] << setw(60) << row[2] << setw(40) << row[3] << endl;
		}


	}
	do
	{
		cout << "\nPress f to finish the operation: ";
		cin >> chose;
		if (chose == "f")
		{
			devmenu();
		}
	} while (chose != "f");

}

void inventory()
{
	system("cls");
	int route;

	cout << "---------------INVENTORY MENU------------------"<<endl;
	cout << "\nACTIVITY CODE              ACTIVITY " << endl;
	cout << "    1		          ADD/UPDATE/DELETE INVENTORY" << endl;
	cout << "    2                     LIST INVENTORY" << endl;
	cout << "    3                     SEARCH INVENTORY" << endl;
	cout << "    4                     BACK TO OWNER MENU" << endl;
	cout << "\n PLEASE ENTER THE ACTIVITY CODE HERE >> ";
	cin >> route;

	if (route == 1)
	{
		audmenu();
	}
	else if (route == 2)
	{
		listInventory();
	}
	else if (route == 3)
	{
		searchInventory();
	}
	else if (route == 4)
	{
		ownermenu();
	}
	else
	{
		cout << "PLEASE ENTER THE AVAILABLE ACTIVITY CODE ONLY, THANKS";
		_getch();
		system("cls");
		inventory();
	}
}

void audmenu()
{
	system("cls");
	int route;

	cout << "-----------ADD/DELETE/UPDATE MENU--------" << endl;
	cout << "\nACTIVITY CODE              ACTIVITY " << endl;
	cout << "    1			  ADD INVENTORY" << endl;
	cout << "    2                     UPDATE INVENTORY" << endl;
	cout << "    3                     DELETE INVENTORY" << endl;
	cout << "    4                     BACK TO INVENTORY MENU" << endl;
	cout << "\nPLEASE ENTER THE ACTIVITY CODE HERE >> ";
	cin >> route;

	switch (route) {
	case 1:
		addInventory();
		break;
	case 2:
		updateInventory();
		break;
	case 3:
		deleteInventory();
		break;
	case 4:
		inventory();
		break;
	default:
		cout << "PLEASE ENTER THE AVAILABLE ACTIVITY CODE ONLY, THANKS";
		_getch();
		system("cls");
		audmenu();
	}
}

//validation inv_name:DONE
//tambah expiry date : DONE
void addInventory()
{
	system("cls");
	string user_id, inv_name,inv_expdate, inv_adddate, inv_quantity, inv_costPrice, inv_sellPrice;

	char choose;
	cout << "-----------------------ADD INVENTORY-----------------------" << endl;
	cin.ignore(1, '\n');
	cout << "\nUSER ID (1-> THE OWNER, 2->TEST ACCOUNT): ";
	getline(cin, user_id);
	cout << "\nNAME: ";
	getline(cin, inv_name);


	// check inv_name in database
	string checkUser_query = "select * from inventory where inv_name = '" + inv_name + "'";
	//compare input dgn data dlm databse
	const char* CU = checkUser_query.c_str();
	qstate = mysql_query(conn, CU); //execute query

	if (!qstate) //boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 1) //inv_name exist
		{
			cout << "\n\nINVENTORY EXIST IN DATABASE. GO TO UPDATE INVENTORY TO EDIT EXISTING ITEM OR ENTER NEW ITEM HERE";
			do
			{
				cout << "\nPress u to update exisiting inventory, a to add another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 'u')
				{
					updateInventory();
				}
				else if (choose == 'a')
				{
					addInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'a' && choose == 'f');


		}
		else
		{
			cout << "\nDATE ADDED INTO STORAGE(dd/mm/yyyy): ";
			getline(cin, inv_adddate);
			cout << "\nEXPIRATION DATE(dd/mm/yyyy)[Note:For inventory that dosen't have expiration date, set expiration date to one year from date added in inventory]: ";
			getline(cin, inv_expdate);
			cout << "\nQUANTITY: ";
			getline(cin, inv_quantity);
			cout << "\nCOST PRICE FOR ONE UNIT OF INVENTORY:RM ";
			getline(cin, inv_costPrice);
			cout << "\nSELL PRICE FOR ONE UNIT OF INVENTORY:RM ";
			getline(cin, inv_sellPrice);



			//compare dgn apa yg dlm database 
			string insert_query = "insert into inventory (user_id,inv_name,inv_expdate,inv_adddate,inv_quantity,inv_costPrice,inv_sellPrice) values ('" + user_id + "','" + inv_name + "', STR_TO_DATE('" + inv_expdate + "','%d/%m/%Y'), STR_TO_DATE('" + inv_adddate + "','%d/%m/%Y'),'" + inv_quantity + "','" + inv_costPrice + "','" + inv_sellPrice + "');";
			const char* q = insert_query.c_str();//convert sebab c++ kena tukar ke char
			qstate = mysql_query(conn, q);//execute

			//YYYY-MM-DD//default date format

			if (!qstate) //query boleh jalan
			{
				cout << endl << "\n\nINVENTORY SUCCESFULLY ADDDED IN DATABASE!" << endl;
				string insert_query = "update inventory set inv_shelflife = datediff( inv_expdate , inv_adddate);";
				const char* q = insert_query.c_str();//convert sebab c++ kena tukar ke char
				qstate = mysql_query(conn, q);//execute

				if (!qstate)
				{
					cout << "\nINVENTORY SHELF LIFE SUCESSFULLY CALCULATED AND ADDED IN DATABASE!"<<endl;
					_getch();
				}
				else
				{
					cout << "\n\nQuery Execution Problem!" << mysql_errno(conn) << endl;
				}
			}
			else //query tak boleh jalan
			{
				cout << "\n\nQuery Execution Problem!" << mysql_errno(conn) << endl;
			}

			do
			{
				cout << "\nPress a to add another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 'a')
				{
					addInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'a' && choose == 'f');
		}

	}
}

//update inv_name validation sebelum update
//tambah expiry date: DONE
//tambah shelf life: DONE
void updateInventory()
{
	int chooseUpdate;
	string inv_name, inv_adddate,inv_expdate,inv_quantity, inv_costPrice, inv_sellPrice, new_inv_name;
	char choose;
	system("cls");
	cin.ignore(1, '\n');
	cout << "\t\t\t\t--------------UPDATE INVENTORY--------------" << endl;
	cout << "ENTER INVENTORY NAME: ";
	getline(cin, inv_name);

	cout << endl;

	// check inv_name in database
	string checkUser_query = "select * from inventory where inv_name = '" + inv_name + "'";
	//compare input dgn data dlm databse
	const char* CU = checkUser_query.c_str();
	qstate = mysql_query(conn, CU); //execute query

	if (!qstate) //boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 0) //inv_name not exist
		{
			cout << "\nINVENTORY NOT EXIST IN DATABASE";

			do
			{
				cout << "\n\nPress u to update another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 'u')
				{
					updateInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'u' && choose == 'f');
		}
		else
		{
			string search_query = "select inv_name,date_format(inv_adddate, '%d %M %Y'),date_format(inv_expdate, '%d %M %Y'), inv_shelflife , inv_quantity, inv_costPrice, inv_sellPrice from inventory where inv_name like '%" + inv_name + "%'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "------------------------------------------------------------" << endl;
					cout << "Inventory Name/1: " << row[0] << endl;
					cout << "Date added to the storage/2: " << row[1] << endl;
					cout << "Inventory Expiration Date/3: " << row[2] << endl;
					cout << "Inventory shelf life(days)/4: " << row[3] << endl;
					cout << "Inventory Quantity/5: " << row[4] << endl;
					cout << "Cost price for one unit/6:RM " << row[5] << endl;
					cout << "Sell price for one unit/7:RM " << row[6] << endl;
					cout << "------------------------------------------------------------" << endl;
				}
				//how to catch empty query?
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			do
			{
				cout << "\nENTER NUMBER TO UPDATE THE ATTRIBUTE: ";
				cin >> chooseUpdate;
				cin.ignore(1, '\n');
				if (chooseUpdate == 1)
				{
					cout << "INSERT NEW INVENTORY NAME: ";
					getline(cin, new_inv_name);
					string update_query = "update inventory set inv_name = '" + new_inv_name + "' where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					afterupdateInv();
				}
				else if (chooseUpdate == 2)
				{
					cout << "INSERT NEW DATE ADDED INTO STORAGE(Enter in this format, dd/mm/yyyy): ";
					getline(cin, inv_adddate);
					string update_query = "update inventory set inv_adddate = STR_TO_DATE('" + inv_adddate + "', '%d/%m/%Y') where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					//This part edited after sending the pdf final report to sv and evaluator so I can't include this specific part in the pseudocode and flowchart of the system
					//Sorry for my carelessness in this part :(
					string insert_query = "update inventory set inv_shelflife = datediff( inv_expdate , inv_adddate);";
					const char* b = insert_query.c_str();//convert sebab c++ kena tukar ke char
					qstate = mysql_query(conn, b);//execute
					afterupdateInv();
				}
				else if (chooseUpdate == 3)
				{
					cout << "INSERT NEW EXPIRATION DATE(Enter in this format, dd/mm/yyyy): ";
					getline(cin, inv_expdate);
					string update_query = "update inventory set inv_expdate = STR_TO_DATE('" + inv_expdate + "', '%d/%m/%Y') where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					//This part edited after sending the pdf final report to sv and evaluator so I can't include this specific part in the pseudocode and flowchart of the system
					//Sorry for my carelessness in this part :(
					string insert_query = "update inventory set inv_shelflife = datediff( inv_expdate , inv_adddate);";
					const char* b = insert_query.c_str();//convert sebab c++ kena tukar ke char
					qstate = mysql_query(conn, b);//execute
					afterupdateInv();
				}
				else if (chooseUpdate == 4)
				{
					cout << "THIS ATTRIBUTE IS THE RESULT OF DAY DIFFERENCE BETWEEN EXPIRATION DATE AND DATE ADDED TO STORAGE DATE. SO, YOU CAN'T EDIT IT ";

						do
						{
							cout << "\n\nPress u to update another inventory, f to finish operation: ";
							cin >> choose;
							if (choose == 'u')
							{
								updateInventory();
							}
							else if (choose == 'f')
							{
								ownermenu();
							}
						} while (choose != 'u' && choose == 'f');
				}
				else if (chooseUpdate == 5)
				{
					cout << "INSERT NEW QUANTITY:  ";
					getline(cin, inv_quantity);
					string update_query = "update inventory set inv_quantity = '" + inv_quantity + "' where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					afterupdateInv();

				}
				else if (chooseUpdate == 6)
				{
					cout << "INSERT NEW COST PRICE FOR ONE UNIT: RM ";
					getline(cin, inv_costPrice);
					string update_query = "update inventory set inv_costPrice = '" + inv_costPrice + "' where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					afterupdateInv();
				}
				else if (chooseUpdate == 7)
				{
					cout << "INSERT SELL PRICE FOR ONE UNIT: RM ";
					getline(cin, inv_sellPrice);
					string update_query = "update inventory set inv_sellPrice = '" + inv_sellPrice + "' where inv_name like '%" + inv_name + "%'";
					const char* q = update_query.c_str();
					qstate = mysql_query(conn, q);
					afterupdateInv();
				}


			} while (chooseUpdate != 1 && chooseUpdate != 2 && chooseUpdate != 3 && chooseUpdate != 4 && chooseUpdate != 5 && chooseUpdate !=6 && chooseUpdate != 7);
		}

	}

	
}

void afterupdateInv()
{
	char choose;
	if (!qstate) //query boleh jalan
	{
		cout << endl << "\nINVENTORY SUCCESFULLY UPDATED IN DATABASE!" << endl;
	}
	else //query tak boleh jalan
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	do
	{
		cout << "Press u to update another inventory, f to finish operation: ";
		cin >> choose;
		if (choose == 'u')
		{
			updateInventory();
		}
		else if (choose == 'f')
		{
			ownermenu();
		}
	} while (choose != 'u' && choose == 'f');
}


//update inv_name validation sebelum delete
void deleteInventory()
{
	system("cls");
	string inv_name;
	char choose;
	cout << "-------------------DELETE INVENTORY--------------" << endl;
	cout << "\nENTER INVENTORY NAME: ";
	cin.ignore(1, '\n');
	getline(cin, inv_name); 

	// check inv_name in database
	string checkUser_query = "select * from inventory where inv_name = '" + inv_name + "'"; 
	//compare input dgn data dlm databse
	const char* CU = checkUser_query.c_str();
	qstate = mysql_query(conn, CU); //execute query

	if (!qstate) //boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 0) //inv_name not exist
		{
			cout << "\nINVENTORY NOT EXIST IN DATABASE";

			do
			{
				cout << "\n\nPress d to delete another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 'd')
				{
					deleteInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'd' && choose == 'f');

		}
		else
		{
			do
			{
				cout << endl;
				cout << "ARE YOU SURE THAT YOU WANT TO REMOVE THIS INVENTORY? (y/n): ";
				cin >> choose;
				if (choose == 'y' || choose == 'Y')
				{

					string delete_query = "delete from inventory where inv_name = '" + inv_name + "'";
					const char* q = delete_query.c_str();
					qstate = mysql_query(conn, q);
					if (!qstate)
					{
						cout << "INVENTORY SUCCESSFULLY DELETED IN DATABASE!";
					}
					else
					{
						cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
					}
				}
				else if (choose == 'n' || choose == 'N')
				{
					inventory();
				}
			} while (choose != 'y' && choose != 'Y' && choose != 'n' && choose != 'N');

			do
			{
				cout << "\n\nPress d to delete another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 'd')
				{
					deleteInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'd' && choose == 'f');
		}

	}


}

//tambah expiry date: DONE
//shelf life somehow fits?: DONE
void listInventory()
{
	system("cls");
	string choose;
	cout << "\t\t\t\t--------------LIST INVENTORY--------------" << endl;

	qstate = mysql_query(conn, "select user_id,inv_name, date_format(inv_adddate, '%d %M %Y'), date_format(inv_expdate, '%d %M %Y'), inv_shelflife, inv_quantity, inv_costPrice, inv_sellPrice from inventory");

	if (!qstate)
	{
		//setw = set width
		cout << setw(5) <<"User ID"<<setw(20)<< "Name" << setw(28) << "Date added to storage" <<setw(22)<< "Expiration date" << setw(20) <<"Shelf life(days)"<<setw(10)<< "Quantity" << setw(29) << "Cost price for one unit(RM)" << setw(28) << "Sell price for one unit(RM)" << endl;

		//body table
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) //fetch every row untill the end of data
		{
			cout << setw(5)<< row[0] << setw(27) << row[1] << setw(20) <<row[2]<<setw(25)<< row[3] << setw(16) << row[4] <<setw(12)<<row[5]<<setw(22) << row[6]<<setw(25)<<row[7] << endl;
		}
	}
	do
	{
		cout << "\nPress u to update inventory, d to delete inventory, f to finish the operation: ";
		cin >> choose;
		if (choose == "u")
		{
			updateInventory();
		}
		else if (choose == "d")
		{
			deleteInventory();
		}
		else if (choose == "f")
		{
			ownermenu();
		}
	} while (choose != "u" && choose != "d" && choose != "f");

	
}

//update inv_name validation sebelum search
//tambah expiry date: DONE
//tambah shelf life: DONE
void searchInventory()
{
	string inv_name;
	char choose;
	system("cls");
	cin.ignore(1, '\n');
	cout << "\t\t\t\t--------------SEARCH INVENTORY--------------" << endl;
	cout << "Search Inventory Name: ";
	getline(cin, inv_name);


	// check inv_name in database
	string checkUser_query = "select * from inventory where inv_name = '" + inv_name + "'";
	//compare input dgn data dlm databse
	const char* CU = checkUser_query.c_str();
	qstate = mysql_query(conn, CU); //execute query

	if (!qstate) //boleh execute
	{
		res = mysql_store_result(conn);
		if (res->row_count == 0) //inv_name not exist
		{
			cout << "\nINVENTORY NOT EXIST IN DATABASE OR INSERT FULL NAME OF THE INVENTORY WHEN SEARCHING THE INVENTORY";

			do
			{
				cout << "\n\nPress s to search another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 's')
				{
					searchInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 'u' && choose == 'f');
		}
		else
		{
			string search_query = "select inv_name,date_format(inv_adddate, '%d %M %Y'),date_format(inv_expdate, '%d %M %Y'), inv_shelflife , inv_quantity, inv_costPrice, inv_sellPrice from inventory where inv_name like '%" + inv_name + "%'";
			const char* q = search_query.c_str();
			qstate = mysql_query(conn, q);

			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << "------------------------------------------------------------" << endl;
					cout << "Inventory Name: " << row[0] << endl;
					cout << "Date added to the storage: " << row[1] << endl;
					cout << "Inventory Expiration Date: " << row[2] << endl;
					cout << "Inventory shelf life(days): " << row[3] << endl;
					cout << "Inventory Quantity: " << row[4] << endl;
					cout << "Cost price for one unit:RM " << row[5] << endl;
					cout << "Sell price for one unit:RM " << row[6] << endl;
					cout << "------------------------------------------------------------" << endl;
				}
			 //how to catch empty query?
			}
			else
			{
				cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
			}
			do
			{
				cout << "\nPress s to search another inventory, f to finish operation: ";
				cin >> choose;
				if (choose == 's')
				{
					searchInventory();
				}
				else if (choose == 'f')
				{
					ownermenu();
				}
			} while (choose != 's' && choose == 'f');
		}

	}

	
}


void revenue()
{
	system("cls");
	step1UpdateRev();
	finalUpdateRev();

}

void step1UpdateRev()
{
	//compare dgn apa yg dlm database
	string clear_query = "delete from revenue";
	const char* q = clear_query.c_str();//convert sebab c++ kena tukar ke char
	qstate = mysql_query(conn, q);//execute

	//YYYY-MM-DD//default date format

	if (!qstate) //query boleh jalan
	{
		cout << endl << "\nOPERAION #1 FOR REVENUE UPDATE COMPLETE" << endl;
	}
	else //query tak boleh jalan
	{
		cout << "\nQuery Execution Problem!" << mysql_errno(conn) << endl;
	}

}

void finalUpdateRev()
{
	//compare dgn apa yg dlm database
	string insert_query = "insert into revenue(user_id,inv_id,revenue_amount,agg_revenue_amount,revenue_state,revenue_percentage) select user_id,inv_id, inv_sellPrice - inv_costPrice, (inv_sellPrice-inv_costPrice) * inv_quantity, if((inv_sellPrice - inv_costPrice) >= 0,'PROFIT','LOSS'),if ((inv_sellPrice - inv_costPrice) >= 0,((inv_sellPrice - inv_costPrice) / inv_costPrice) * 100,(-(inv_sellPrice - inv_costPrice) / inv_costPrice) * 100)  from inventory";
	const char* q = insert_query.c_str();//convert sebab c++ kena tukar ke char
	qstate = mysql_query(conn, q);//execute


	if (!qstate) //query boleh jalan
	{
		cout << endl << "\nREVENUE SUCESSFULLY UPDATED IN DATABASE!" << endl;
	}
	else //query tak boleh jalan
	{
		cout << "\nQuery Execution Problem!" << mysql_errno(conn) << endl;
	}
}

//kena tambah shelf life?
void report()
{
	string choose;
	revenue();
	system("cls");
	
	cout << "\t\t\t\t--------------PROFIT/LOSS REPORT--------------" << endl;

	qstate = mysql_query(conn,"select i.inv_name, i.inv_adddate, i.inv_expdate, i.inv_shelflife,i.inv_quantity, r.revenue_amount, r.agg_revenue_amount, r.revenue_state, r.revenue_percentage from inventory i inner join revenue r on r.inv_id = i.inv_id; ");

	if (!qstate)
	{
		//setw = set width
		cout << endl;
		cout << setw(12) << "Inventory Name" << setw(35) << "Date added to storage" << setw(20)<<"Expiration date"<< setw(20)<<"Shelf life(days)"<<setw(13)<<"Quantity"<<setw(14) << "Revenue(RM)" << setw(25) << "Aggregate Revenue(RM)" << setw(9) << "State" << setw(17) << "Percentage(%)" << endl;

		//body table
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) //fetch every row untill the end of data
		{
			cout << setw(25) << row[0] << setw(19) << row[1] << setw(22) << row[2] << setw(17) << row[3] << setw(17) << row[4] << setw(10) << row[5] << setw(22)<<row[6]<<setw(19)<<row[7]<<setw(15)<<row[8]<<endl;
		}

	   
	}

	string insert_query = "select (select count(inv_id) from inventory), (select sum(inv_quantity) from inventory),sum(revenue_amount), sum(agg_revenue_amount), if(sum(revenue_amount)>=0, 'PROFIT', 'LOSS'),if(sum(revenue_amount)>=0, sum(revenue_amount)/(select sum(inv_costPrice) from inventory) * 100, -(sum(revenue_amount))/(select sum(inv_costPrice) from inventory) * 100) from revenue ";
	const char* q = insert_query.c_str();//convert sebab c++ kena tukar ke char
	qstate = mysql_query(conn, q);//execute

	if (!qstate)
	{

		//body table
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) //fetch every row untill the end of data
		{
			cout << "\n\nTYPES OF INVENTORY IN STORAGE:" << row[0] << endl;
			cout << "TOTAL INVENTORY IN STORAGE: " << row[1] << endl;
			cout << "TOTAL REVENUE: " << row[2] << endl;
			cout << "TOTAL AGGREGGATE REVENUE: " << row[3] << endl;
			cout << "REVENUE STATE: " << row[4] << endl;
			cout << "TOTAL REVENUE PERCENTAGE: " << row[5] << endl;
		}
	}



	do
	{
		cout << "\nPress f to finish the operation: ";
		cin >> choose;
		if (choose == "f")
		{
			ownermenu();
		}
	} while (choose != "f");

}


