//include header files
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <windows.h>
	using namespace std;

	//function headers
	void header();
	bool excessinputvalidation();
	void datatypevalidation(int* sentinel);
	void assignseatsnum(int seating[3][60]);
	void showtime_details(string[3][3]);
	int check_date(string showtimes[3][3], int &sentinel);
	void ticketdetails(double ticketprices[3][3], int[3][3], int seatcap[3], int day);
	int check_class(double ticketprices[3][3], int seatcount[3][3], int seatcap[3], int day);
	int check_ticket(int &sentinel, int Class, int seatcount[3][3], int seatcap[3], int day);
	void showseats(int Class, int seating[3][60], int* m, int* n, int day);
	void seatselection(int Class, int num, int total, int seatschosen[30], int seating[3][60], int day);
	void snackitems(double snacksprices[3][3]);
	int snackselection(int, int &sentinel);
	bool billing(int Class, double ticketprices[3][3], double snacksprices[2][3], int snackschosen[3], int NumAdult, int NumChild, int NumStudent, string promocode);
	void ticketprinting(int total, int NumAdult, int NumChild, int NumStudent, int Class, string movie, string date, string time, int seatschosen[30], double ticketprices[3][3], int snackschosen[3], bool promo);
	bool proceed();
	void salesreport(string showtimes[3][3], int catseatcount[3][3][3], int seatcount[3][3], int seatcap[3], double ticketprices[3][3], int totalsnackschosen[3], double snacksprices[2][3], int totalpromo);



	void main()
	{
		//define constants
		const string date1 = "03/01/2020", date2 = "04/01/2020", date3 = "05/01/2020"; // dates where the movie will be shown
		const string movie1 = "Clueless", movie2 = "The Grand Buddapest Hotel", movie3 = "Huges High";
		const string time1 = "7.30pm", time2 = "7.00pm", time3 = "8.00pm";
		const int totalseats0 = 15, totalseats1 = 15, totalseats2 = 30;
		const double price0adult = 20, price1adult = 16, price2adult = 18, price0child = 10, price1child = 6, price2child = 8, price0student = 12, price1student = 8, price2student = 10;
		const double popcornprice = 10, cookieprice = 4, softdrinkprice = 2, Oripopcornprice = 11.50, Oricookieprice = 5, Orisoftdrinkprice = 2.5;
		const string promocode = "PV738"; // promocode for staff to get free popcorn


		// startscreen

		//declare variables
		string date, movie, time;
		string showtimes[3][3] = { { date1 , date2, date3 },{ time1, time2, time3 },{ movie1, movie2, movie3} }; //array to store showdates,showtimes and movie titles.
		int moviecount[3] = { 0 }; // total seats taken for each movie
		int seatcap[3] = { totalseats0, totalseats1, totalseats2 }; // seat capacity for each class
		int seatcount[3][3] = { 0 }; // total seats taken for: each movie(2D), each class (1D)
		int catseatcount[3][3][3] = { 0 }; // total seats taken for: each movie(3D), each category (2D), each class (1D)
		double ticketprices[3][3] = { { price0adult, price1adult, price2adult },{ price0child, price1child, price2child },{ price0student, price1student, price2student } }; //ticket prices for: each category(2D), each class (1D)
		double snacksprices[2][3] = { {popcornprice, cookieprice, softdrinkprice }, { Oripopcornprice, Oricookieprice, Orisoftdrinkprice } }; // discounted price, ori price 
		int seating[3][60] = { 0 }; // seat numbers to be sold in the system for: each movie(2D), each movie seat (1D) 
		int totalsnackschosen[3] = { 0,0,0 }; // total snacks sold in all the showtimes
		int totalpromo = 0; //total number of promocode used
		int day;
		int NumAdult = 0, NumStudent = 0, NumChild = 0;
		bool confirm;

		//assign seat number for all movies
		assignseatsnum(seating);

		//logo
		string description = "PROUDLY PRESENTED BY.... TARUC FOCS\n\nClassic movies every Friday, Saturday and Sunday!\n\n";
		cout << setw(100) << setfill('-') << "\n\n" << setfill(' ');
		cout << " _____  _    ____     ____ _                                 \n";
		cout << "|_   _|/ \\  |  _ \\   / ___(_)_ __   ___ _ __ ___   __ ___  __\n";
		cout << "  | | / _ \\ | |_) | | |   | | '_ \\ / _ \\ '_ ` _ \\ / _` \\ \\/ /\n";
		cout << "  | |/ ___ \\|  _ <  | |___| | | | |  __/ | | | | | (_| |>  < \n";
		cout << "  |_/_/   \\_\\_| \\_\\  \\____|_|_| |_|\\___|_| |_| |_|\\__,_/_/\\_\\\n\n";
		cout << " _____ _      _        _   _               ____            _                \n";
		cout << "|_   _(_) ___| | _____| |_(_)_ __   __ _  / ___| _   _ ___| |_ ___ _ __ ___\n";
		cout << "  | | | |/ __| |/ / _ \\ __| | '_ \\ / _` | \\___ \\| | | / __| __/ _ \\ '_ ` _ \\\n";
		cout << "  | | | | (__|   <  __/ |_| | | | | (_| |  ___) | |_| \\__ \\ ||  __/ | | | | |\n";
		cout << "  |_| |_|\\___|_|\\_\\___|\\__|_|_| |_|\\__, | |____/ \\__, |___/\\__\\___|_| |_| |_|\n";
		cout << "		                   |___/         |___/      \n\n";
		cout << setw(100) << setfill('-') << "\n\n" << setfill(' ');
		for (size_t i = 0; i < description.length(); i++)
		{
			cout << description.at(i); //display text letter by letter
			Sleep(20);
		}
		system("pause");


		//selling starts

		//loop for ticketing to repeat the ticketing process multiple times
		do
		{
			system("cls");
			header();

			//display available showtimes
			showtime_details(showtimes);

			//choosing of date 
			int sentinel = 0;
			do
			{
				day = check_date(showtimes, sentinel);

				if (moviecount[day] == (seatcap[0] + seatcap[1] + seatcap[2]))
				{
					cout << "\nSorry, all tickets for this movie has been sold out, please pick another movie";
					sentinel = 0;
				}
				if (sentinel == -999)
				{
					//assign date, movie and time
					date = showtimes[0][day];
					time = showtimes[1][day];
					movie = showtimes[2][day];

					cout << left << setw(30) << "Movie" << right << ": " << movie << endl; //display movie chosen
					cout << left << setw(30) << "Time" << right << ": " << time << endl << endl; //display time chosen
					cout << "~ Counter is now open for selling of tickets ~\n\n";
				}
			} while (sentinel != -999);
			system("pause");

			//ticket selling
			system("cls");
			header();
			int total = 0;//total number of tickets bought per user.
			int seatschosen[30] = { 0 }; // records seats chosen per user
			int snackschosen[3] = { 0 }; //records snacks chosen per user

			//obtain class
			cout << "\nClass Selection\n";
			ticketdetails(ticketprices, seatcount, seatcap, day); //display ticket information
			int Class = check_class(ticketprices, seatcount, seatcap, day); //users choose class

			while (seatcount[day][Class] == seatcap[Class]) //prompts user to enter again when the tickets for class chosen are sold out
			{
				cout << "Sorry, tickets for class" << Class << " is sold out, please choose another class\n\n";
				Class = check_class(ticketprices, seatcount, seatcap, day);
			}
			//display note for class 0 ticket selection
			if (Class == 0)
				cout << "\n*You may dismiss the zero at the front while entering your desired seat number\n(eg. 001 can be written as 01 or 1)\n\n";
			system("pause");
			system("cls");
			header();

			do
			{
				cout << "\nTicket Purchasing - Class " << Class;

				//loop for ticket sales of the three categories
				for (size_t j = 0; j < 3; j++)
				{
					string category;
					int num; //number of tickets

					//assign category
					if (j == 0)
						category = " Adult ";
					else
						j == 1 ? category = " Child " : category = "Student";

					//let users enter number of tickets required
					sentinel = 0;
					while (sentinel == 0)
					{
						cout << "\n\n" << left << "Number of " << category << " seat(s) required" << right << ": ";
						num = check_ticket(sentinel, Class, seatcount, seatcap, day);
						if (num == -99)
							sentinel = 0;
					}
					//update when number of tickets required is more than 0
					if (num > 0)
					{
						catseatcount[day][j][Class] += num; //update total amount of class(cl) ticket sold
						seatcount[day][Class] += num; //update total amount of adult ticket sold
						seatselection(Class, num, total, seatschosen, seating, day); // call function to choose seating
						total += num;//update total of tickets bought per user.
						moviecount[day] += num; //update total tickets sold for each movie
					}
					//assign number of tickets chosen for each category
					if (j == 0)
						NumAdult = num;
					else
						j == 1 ? NumChild = num : NumStudent = num;
				}
				//remind user to buy at least one ticket
				if (total == 0)
					cout << "\n\nPlease purchase at least one ticket.\n";
			} while (total == 0);

			system("pause");
			system("cls");
			header();

			//snacks selection
			snackitems(snacksprices); //display snack prices
			//loop to display prompt three times for three snacks
			for (size_t i = 0; i < 3; i++)
			{
				string snack;
				//assign snack for each iteration of loop
				if (i == 0)
					snack = "   popcorn   ";
				else
					i == 1 ? snack = "   cookies   " : snack = " soft drinks ";
				//prompt for users to enter snacks required
				sentinel = 0;
				while (sentinel != -999)
				{
					cout << "\nNumber of" << snack << "required: ";
					snackschosen[i] = snackselection(total, sentinel); //record snack chosen per user
				}
				totalsnackschosen[i] += snackschosen[i]; //update total snacks sold
			}
			system("pause");
			system("cls");
			header();

			// billing
			bool promo = billing(Class, ticketprices, snacksprices, snackschosen, NumAdult, NumChild, NumStudent, promocode);
			if (promo == true)
				totalpromo += 1; // update the quantity of promo code used 

			//ticket printing
			cout << "\n\nHere are your tickets: \n\n";
			ticketprinting(total, NumAdult, NumChild, NumStudent, Class, movie, date, time, seatschosen, ticketprices, snackschosen, promo);

			confirm = false;
			if ((3 * (seatcap[0] + seatcap[1] + seatcap[2]) - moviecount[0] - moviecount[1] - moviecount[2]) > 0)
			{
				cout << "Next customer? (y = yes, n = no) >> ";
				confirm = proceed();
			}
		} while (confirm == true);

		system("cls");
		header();

		//sales report
		salesreport(showtimes, catseatcount, seatcount, seatcap, ticketprices, totalsnackschosen, snacksprices, totalpromo);
		system("pause");
	}


	//function to display header
	void header()
	{
		cout << "\n   T  A  R   C  i  n  e  m  a  x\n";
		cout << setw(120) << setfill('-') << "\n" << setfill(' ');
	}


	//function to check if user enters excess input
	bool excessinputvalidation()
	{	//initialize variables
		char extrainput[500] = "";
		bool null = true;

		cin.getline(extrainput, 300); //records any excess input

		//check the excess inputs for non-null values
		for (size_t i = 0; i < strlen(extrainput); i++)
			if (!(isspace(extrainput[i])))//if excess input is detected
			{
				null = false;
				break;
			}
		return null;
	}


	//function to validate data types
	void datatypevalidation(int* sentinel)
	{
		if (cin.fail()) //if input failure occurs
		{
			cin.clear(); // clear buffer
			cin.ignore(99999, '\n'); //skips to next newline
			*sentinel = -99;
		}
	}


	//function to assign seat number to the seating array
	void assignseatsnum(int seating[3][60])
	{
		//loop for each day
		for (size_t day = 0; day < 3; day++)
		{
			//assign seat numbers
			for (size_t i = 0; i <= 59; i++)
			{
				if (i <= 14)
					seating[day][i] = i + 101; //seat numbers are 101 t0 115 for the first 15 spaces
				else if (i <= 29)
					seating[day][i] = i - 14; //seat numbers are 001 t0 015 for the next 15 spaces
				else
					seating[day][i] = i + 171; //seat numbers are 201 t0 230 for the remaining 30 spaces
			}
		}
	}


	//function to display movie showtimes
	void showtime_details(string showtimes[3][3])
	{
		cout << "Showtimes:\n";

		for (size_t i = 0; i < 3; i++) //loops information for each date
		{
			for (size_t j = 0; j <= 2; j++) //loops information for movie, showdate or showtime
			{
				if (j == 2)
					cout << "- ";

				cout << showtimes[j][i] << " "; // displays information from the showtimes array
			}
			cout << endl;
		}
	}


	//function to get date from user
	int check_date(string showtimes[3][3], int &sentinel)
	{//user inputs date
		string date;
		cout << "\nDate (using format DD/MM/YYYY): ";
		cin >> date;

		bool null = excessinputvalidation(); 	//check if user enters excess input

		//check if the date entered matches with the array
		sentinel = 0;
		int i = 0;
		if (null == true)
		{
			for (; sentinel == 0 && i < 3; i++)
				if (date == showtimes[0][i])
					sentinel = -999; //assign sentinal value to terminate loop
		}

		//reminds user to type in a valid date
		if (sentinel == 0)
			cout << "Please enter a valid date using the format given\n";

		return i - 1; //returns the value of i in showtimes[0][i] when (date == showtimes[0][i])
	}


	//function to show ticket prices, available seats, and general rules for ticket selling
	void ticketdetails(double ticketprices[3][3], int seatcount[3][3], int seatcap[3], int day)
	{	//for loop to display prices
		cout << "\nClass:    0        1        2 ";
		for (size_t j = 0; j < 3; j++)
		{
			if (j == 0)
				cout << "\nAdult   ";
			else if (j == 1)
				cout << "\nChild   ";
			else
				cout << "\nStudent ";
			for (size_t k = 0; k < 3; k++)
				cout << "RM " << left << setw(4) << ticketprices[j][k] << "  ";
		}
		//for loop to display number of available seats
		cout << "\n\n\n" << right << setw(25) << "Seats available:\n";
		for (size_t i = 0; i < 3; i++)
			cout << setw(16) << "Class " << i << " - " << seatcap[i] - seatcount[day][i] << endl;

		//display general rules for ticket selling
		cout << "\n\nNote: Only children under the age of 12 are eligible to purchase a child ticket.\n      A valid Student registration card must be presented to be eligible to purchase a student ticket.\n      Users are required to choose seats where the first number is same with the chosen class.\n      Seats with the seat number of 000 are already sold out\n";
	}


	// function to get class from user
	int check_class(double ticketprices[3][3], int seatcount[3][3], int seatcap[3], int day)
	{	//declare variables
		char Class;
		int sentinel = 0;

		//while loop to get class and evaluate its validity
		while (sentinel == 0)
		{
			cout << "\n\nEnter desired class (0, 1, 2): ";
			cin >> Class; //user inputs class

			bool null = excessinputvalidation(); //check if user enters excess input

			//remind users to enter only one digit
			if (null == false)
				cout << "Please only enter one digit\n\n";

			//remind users to enter a valid digit
			else if (Class != '0' && Class != '1' && Class != '2')
				cout << "Please enter a valid digit\n\n";

			else
				sentinel = -999; //assign sentinel value to terminate loop in the calling functionin calling function
		}
		return (int)Class - 48; // *ASCII value for char '0' is 48
	}


	//function to get number of tickets required from user
	int check_ticket(int &sentinel, int Class, int seatcount[3][3], int seatcap[3], int day)
	{
		int num = 0;
		if (seatcount[day][Class] == seatcap[Class])
		{
			cout << "Sorry, tickets sold out\n"; // displays message and breaks loop if tickets are sold out
			sentinel = -999;
		}
		else
		{
			cin >> num; //user inputs number of tickets required

			bool null = excessinputvalidation(); //check if user enters excess input
			datatypevalidation(&sentinel);//Check data type

			if (sentinel != -99)
			{
				//tells user to enter a valid number
				if (null == false)
					cout << "Please enter a valid number\n\n";

				//reminds user to enter an appropriate number of tickets required
				else if (num < 0 || num >(seatcap[Class] - seatcount[day][Class]))
					cout << "Please enter a number between 0 and " << seatcap[Class] - seatcount[day][Class] << "\n\n";

				//assign sentinel value to terminate loop in calling function
				else
					sentinel = -999;
			}
			else
			{
				cout << "Please enter a valid number\n";
				num = -99;
			}
		}
		return num; //return number of seats required
	}


	//function to show seats available
	void showseats(int Class, int seating[3][60], int* m, int* n, int day)
	{
		//display seating positions and available seating
		cout << "\n[------------movie--screen------------]\n    ";
		for (size_t i = 0; i <= 59; i++)
		{
			cout << setw(3) << setfill('0') << seating[day][i] << " " << setfill(' ');
			if (i == 6 || i == 14 || i == 21 || i == 29 || i == 39 || i == 49 || 1 == 59)
			{
				cout << endl;
				if (i == 6 || i == 14 || i == 21)
					cout << "    ";
			}
		}

		//switch to determine seat numbers for each class   *from seating[m] to seating[n]
		switch (Class)
		{
		case 1:
			*m = 0;
			*n = 14;
			break;

		case 0:
			*m = 15;
			*n = 29;
			break;

		case 2:
			*m = 30;
			*n = 59;
		} // m and n represents the minimum and maximum index of the seat numbers for each class
	}


	//function for selection of seat number
	void seatselection(int Class, int num, int total, int seatschosen[30], int seating[3][60], int day)
	{
		int m = 0, n = 0; //minimum and maximum 1D index of seat number for class in the seating[3][60] array
		//show seats and assign m and n
		showseats(Class, seating, &m, &n, day);

		cout << "\n\n\nPlease pick " << num << " seat(s) of your choice: \n"; 	//instruction title

		//for loop to process multiple seat numbers
		for (size_t i = 0; i < num; i++)
		{  //do while loop to read and check for each seat number
			int sentinel;
			do {
				sentinel = 0;
				cout << i + 1 << ". ";
				cin >> seatschosen[i + total];	//user inputs seat number

				bool null = excessinputvalidation(); //check if user enters excess input
				if (null == false)
					sentinel = -99;
				else
				{   //check for data type of seatschosen
					datatypevalidation(&sentinel);

					if (sentinel != -99)
					{
						for (size_t j = 0; j < (i + total) && sentinel != 99; j++)
						{  //check if the entered seat number has been chosen before
							if (seatschosen[i + total] == seatschosen[j])
							{
								cout << "you have already chosen this seat, please pick another one\n\n";
								sentinel = 55;
							}
						}
						if (sentinel != 55)
						{  //check if the entered seat number is valid
							for (size_t j = m; j <= n && sentinel != -999; j++)
								//entered seat number is not 0 and seat number chosen matches with the available seat numbers 
								if (seatschosen[i + total] != 0 && seatschosen[i + total] == seating[day][j])
								{
									seating[day][j] = 0; //remove seats from available seatings
									sentinel = -999; //assign sentinel value to terminate while loop
								}
						}
					}
				}
				// reminds user to enter a valid seat number
				if (sentinel == -99)
					cout << "Please enter a valid number.\n\n";

				else if (sentinel == 0)
					cout << "Please enter an available seat number from class " << Class << ".\n\n";// reminds user to enter an available seat number from the class chosen
			} while (sentinel != -999);
		}
	}


	//for loop to display snack prices
	void snackitems(double snacksprices[3][3])
	{
		cout << "\n~ ~ ~ Snack Add-ons ~ ~ ~\n\n\nPrice:      Add-on    Regular   save up: ";
		for (size_t k = 0; k < 3; k++) // assign snack name for each loop
		{
			if (k == 0)
				cout << "\nPopcorn     ";
			else if (k == 1)
				cout << "\nCookies     ";
			else
				cout << "\nSoft Drink  ";
			//display discounted price, normal price and the amount saved up 
			cout << "RM " << left << setw(4) << snacksprices[0][k] << "    " << "RM " << left << setw(4) << snacksprices[1][k] << "    " << "RM" << snacksprices[1][k] - snacksprices[0][k];
		}//display note
		cout << "\n\nNote: A maximum of one popcorn, one cookie and one soft drink can be bought together with each ticket.\n      TARUC Staff can enter your promo code while billing to enjoy a complimentary bucket of popcorn, do not buy here.\n\n";
	}


	//function for users to purchase add-on snacks
	int snackselection(int total, int &sentinel)
	{
		int num;
		sentinel = 0;

		cin >> num; //read number of snacks required
		bool null = excessinputvalidation();	//check if user enters excess input

		if (null == false)
			sentinel = -99;
		else
		{
			datatypevalidation(&sentinel);//Check data type

			if (sentinel != -99)
			{   //reminds user to enter an appropriate number of tickets required
				if (num < 0 || num > total)
					cout << "Please enter a number between 0 and " << total << "\n"; //display error message asking user to pay an amount not less than the fees
				else
					sentinel = -999; //assign sentinel value to terminate loop in calling function
			}
		}
		if (sentinel == -99)
			cout << "Please enter a valid number\n"; //Display error message asking user to enter a valid number
		return num;
	}


	//function for bill calculation
	bool billing(int Class, double ticketprices[3][3], double snacksprices[2][3], int snackschosen[3], int NumAdult, int NumChild, int NumStudent, string promocode)
	{
		cout << "\nBill Calculation - Class " << Class;
		if (NumAdult > 0)
			cout << "\n\nAdult tickets   : " << NumAdult << " @ RM " << setw(2) << ticketprices[0][Class] << " = RM " << ticketprices[0][Class] * NumAdult; //display if user has bought it
		if (NumChild > 0)
			cout << "\nChild tickets   : " << NumChild << " @ RM " << setw(2) << ticketprices[1][Class] << " = RM " << ticketprices[1][Class] * NumChild; //display if user has bought it
		if (NumStudent > 0)
			cout << "\nStudent tickets : " << NumStudent << " @ RM " << setw(2) << ticketprices[2][Class] << " = RM " << ticketprices[2][Class] * NumStudent; //display if user has bought it
		if (snackschosen[0] > 0)
			cout << "\nPopcorn         : " << snackschosen[0] << " @ RM " << setw(2) << snacksprices[0][0] << " = RM " << snacksprices[0][0] * snackschosen[0]; //display if user has bought it
		if (snackschosen[1] > 0)
			cout << "\nCookie          : " << snackschosen[1] << " @ RM " << setw(2) << snacksprices[0][1] << " = RM " << snacksprices[0][1] * snackschosen[1]; //display if user has bought it
		if (snackschosen[2] > 0)
			cout << "\nSoft Drink      : " << snackschosen[2] << " @ RM " << setw(2) << snacksprices[0][2] << " = RM " << snacksprices[0][2] * snackschosen[2]; //display if user has bought it

		double payment;  //amount that the users pays
		// amount to be paid
		double fees = ticketprices[0][Class] * NumAdult + ticketprices[1][Class] * NumChild + ticketprices[2][Class] * NumStudent + snacksprices[0][0] * snackschosen[0] + snacksprices[0][1] * snackschosen[1] + snacksprices[0][2] * snackschosen[2];
		string pcode;
		cout << setw(36) << setfill('-') << "\n" << setfill(' ') << setw(31) << left << "\nTotal:" << "RM " << fees << "\nPromo Code\n(3 tries, enter 0 if not applicable): ";

		int sentinel;
		bool promo = false;
		for (size_t j = 0; j < 3 && pcode != "0" && promo == false; j++)
		{
			if (j > 0)
				cout << setw(32) << left << "\nCode incorrect, please try again: "; //display error message if the user failed to type in correctly the first time
			cin >> pcode; // read pcode

			bool null = excessinputvalidation();  //check if user enters excess input
			if (null == false)
				promo = false; //reject code if there's excess value
			else if (pcode == promocode)
			{
				cout << "Code accepted\n";
				promo = true; //accept code if the input matches with the promo code and theres no excess input
			}
			if (pcode == "0" && null == false)
				pcode = ""; // clear input if user enters 0
			if (promo == false && j == 2 && pcode != "0")
				cout << "Sorry, code is incorrect and you've used up your three tries\n"; //display message when user has tried and failed for three times
		}
		do
		{
			cout << setw(31) << left << "\nPayment: " << "RM ";
			cin >> payment; //read payment

			bool null = excessinputvalidation(); //check if user enters excess input
			sentinel = 0;
			datatypevalidation(&sentinel); 	//check for data type of payment

			if (sentinel == -99)
				cout << "Please enter a valid number\n\n"; //display error message for input error
			else if (null == false)
			{
				sentinel = 99;
				cout << "Please enter only one number\n"; //display error message for entering excess input
			}
			else if (payment < fees)
			{
				sentinel = 99;
				cout << "Please pay an amount that is not less than RM " << fees << endl; //display error message when user enters an insufficient amount of money
			}
		} while (abs(sentinel) == 99);
		cout << setw(30) << left << "Change due: " << "RM " << payment - fees << endl << endl; //display change due

		system("pause");
		system("cls");
		return promo;
	}

	//function for ticket printing
	void ticketprinting(int total, int NumAdult, int NumChild, int NumStudent, int Class, string movie, string date, string time, int seatschosen[30], double ticketprices[3][3], int snackschosen[3], bool promo)
	{
		int cat;
		string category;

		for (size_t j = 0; j < total; j++)
		{
			if (NumAdult > 0 && j < NumAdult) //category is adult for the first round of loop
			{
				category = "Adult  ";
				cat = 0;
			}
			else if (NumChild > 0 && j < NumAdult + NumChild) //category is adult for the second round of loop
			{
				category = "Child  ";
				cat = 1;
			}
			else
			{
				category = "Student"; //category is adult for the third round of loop
				cat = 2;
			}
			//display movie and seating details on ticket
			cout << setw(120) << right << setfill('=') << "\n\n" << setfill(' ');
			cout << left << setw(70) << "TAR Cinemax Ticket" << category << " Class " << Class << endl << endl;
			cout << setw(8) << "Movie" << ": " << movie << endl << setw(8) << "Date" << ": " << date << endl << setw(8) << "Time" << ": " << time << endl << endl;
			cout << "Seat No [ " << setw(3) << setfill('0') << right << seatschosen[j] << setfill(' ') << " ] " << setw(64) << "Price: RM " << ticketprices[cat][Class] << endl << endl;
			cout << setw(120) << setfill('=') << "\n\n" << setfill(' ');
		}
		if (snackschosen[0] + snackschosen[1] + snackschosen[2] > 0 || promo == true) //if user has bought any snacks or enter the promo code correctly
		{
			cout << setw(120) << setfill('=') << "\n\n" << setfill(' ');
			cout << "Snack Redemption Coupon\n\n";
			if (snackschosen[0] > 0)
				cout << left << setw(15) << "Popcorn" << " x " << setw(2) << snackschosen[0] << endl; //display if user has bought any
			if (snackschosen[1] > 0)
				cout << left << setw(15) << "Cookie" << " x " << setw(2) << snackschosen[1] << endl; //display if user has bought any
			if (snackschosen[2] > 0)
				cout << left << setw(15) << "Soft Drink" << " x " << setw(2) << snackschosen[2] << endl; //display if user has bought any
			if (promo == true)
				cout << "\n**Complimentary popcorn " << " x 1" << endl; //display if user has entered promo code correctly
			cout << "\nNote: Snacks are available for collection an hour before the movie starts.\n"; // display code
			cout << setw(120) << right << setfill('=') << "\n\n" << setfill(' ') << endl << endl;
		}
		system("pause");
	}


	//function to determine whether the program should proceed to the next step or to continue on looping
	bool proceed()
	{
		char input;
		bool null;
		cin >> input; //read input
		null = excessinputvalidation(); //check if there's excess input

		while (null == false || (toupper(input) != 'Y' && toupper(input) != 'N')) //null is false and user did not enter y,Y,n or N
		{
			cout << "\nPlease enter a valid option (y = yes, n = no):";//prompt user to enter again
			cin >> input;
			null = excessinputvalidation();//check if there's excess input
		}
		if (toupper(input) == 'Y')
			return true;
		else
			return false;
	}


	//function to display sales report
	void salesreport(string showtimes[3][3], int catseatcount[3][3][3], int seatcount[3][3], int seatcap[3], double ticketprices[3][3], int totalsnackschosen[3], double snacksprices[2][3], int totalpromo)
	{
		for (size_t day = 0; day < 3; day++)
		{
			cout << "\nSALES REPORT " << day + 1 << "\n\n"; //display sales report title
			int clseats = 0, clquantitysold = 0, catseats = 0;
			double catsales = 0;
			cout << "Movie Title: " << showtimes[2][day] << endl; //display movie
			cout << "Date       : " << showtimes[0][day] << endl; //display date
			cout << "Time       : " << showtimes[1][day] << endl << endl; // display time


			cout << right << "SEAT OCCUPANCY FOR EACH CLASS: \n" << setw(60) << "Total Seats    Quantity Sold    Percentage Sold\n";
			for (size_t i = 0; i < 3; i++) //display seat ocupancy for each class
			{
				cout << "Class " << i << "\t\t" << seatcap[i] << "\t\t" << seatcount[day][i] << "\t\t" << fixed << setprecision(2) << 100.0* seatcount[day][i] / seatcap[i] << "%\n"; //Display total seats, quantity sold and percentage sold 
				clseats += seatcap[i]; //update total seats for each class
				clquantitysold += seatcount[day][i]; //update total quantity sold for each day
			}
			cout << "\t\t" << setw(4) << setfill('-') << "\t\t" << setw(5) << " \t\t" << setw(8) << "\n" << setfill(' ');
			cout << "Overall:\t" << clseats << "\t\t" << clquantitysold << "\t\t" << 100.0 * clquantitysold / clseats << "%\n\n"; //Display total seats, total quantity sold and total percentage sold

			cout << "\nSALES FOR EACH CATEGORY TYPE: \n" << setw(41) << "Total Seats         Sales(RM)\n";
			for (size_t i = 0; i < 3; i++) //display sales for each category type
			{
				string cat;
				if (i == 0)
					cat = "Adult"; // assign the category for each loop
				else
					i == 1 ? cat = "Child" : cat = "Student";
				//Display total seats sold and sales for the respective category
				cout << cat << "\t\t" << catseatcount[day][i][0] + catseatcount[day][i][1] + catseatcount[day][i][2] << "\t\t" << fixed << setprecision(2) << catseatcount[day][i][0] * ticketprices[i][0] + catseatcount[day][i][1] * ticketprices[i][1] + catseatcount[day][i][2] * ticketprices[i][2] << endl;
				catseats += catseatcount[day][i][0] + catseatcount[day][i][1] + catseatcount[day][i][2]; //update catseats
				catsales += catseatcount[day][i][0] * ticketprices[i][0] + catseatcount[day][i][1] * ticketprices[i][1] + catseatcount[day][i][2] * ticketprices[i][2]; //update catsales
			}
			cout << "\t\t" << setw(4) << setfill('-') << "\t\t" << setw(9) << " \t\t" << setfill(' ') << endl;
			cout << "Overall:\t" << catseats << "\t\t" << catsales << "\n\n"; //Display total seats sold and sales for the respective category
			cout << setw(120) << setfill('=') << "\n\n" << setfill(' ');
		}

		int  snackquantitysold = 0;
		double snacksales = 0; //initialize variables

		cout << "\nSALES FOR EACH ADD-ON SNACK: \n" << setw(42) << "Quantity Sold        Sales(RM)\n";
		for (size_t i = 0; i < 3; i++)
		{
			string cat;
			if (i == 0)
				cat = "Popcorn\t\t"; //assign snacks for each loop
			else
				i == 1 ? cat = "Cookie\t\t" : cat = "Soft Drink\t";

			cout << cat << totalsnackschosen[i] << "\t\t" << fixed << setprecision(2) << snacksprices[0][i] * totalsnackschosen[i] << endl; //display quantity sold and sales
			snacksales += snacksprices[0][i] * totalsnackschosen[i]; //update total sales
			snackquantitysold += totalsnackschosen[i];	//update total quantity of snacks sold
		}
		cout << "\t\t" << setw(7) << setfill('-') << "\t\t" << setw(11) << " \t\t" << endl;
		cout << "Overall:\t" << snackquantitysold << "\t\t" << snacksales << "\n\n"; //Display total quantity of snack sold and total sales of snacks

		cout << "QUANTITY OF PROMOCODE REDEMPTIONS: " << totalpromo << endl; //Display total quantity of promo code used
	}