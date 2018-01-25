/*
 *Filename: Program 1
 *Name: Levi Lowe
 *WSUID: J298T623
 *HW: HW1
 *Description: This program will use structs to represent bank accounts and money,
                while using functions to interact with the accounts.
 */
#include <iomanip>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Money {
    int dollars;
    int cents;
    };

struct Account {
    string accountName;
    double interest;
    Money balance;
    };

Account createAccount();

Account deposit(Account account, Money deposit);

Money withdraw(Account &account, Money withdraw);

void accrue(Account &account);

void print(Account account);

void print(Money money);



int main()
{
//Setting my structs using a newly learned convention
    Account savings = {"Savings", 0.0, {50, 0}};
    Account checking = {"Checking", 0.0, {10, 0}};
    Money paycheck = {50,0};
    Money feeHBO = {14, 99};
    Money unexpectedExpense = {200, 0};
    Money invalidAmount = {-10, 0};

    cout << endl;
    cout << "In Savings, you have ";
    print(savings);
    cout << ". \n";
    cout << "In Checking, you have ";
    print(checking);
    cout << ". \n";
    cout << endl;

//Accounting for a rounding issue I couldn't solve using round
    Account RothIRA = createAccount();
    RothIRA.balance.cents += 1;
    cout << "In your Roth IRA, you have ";
    print(RothIRA);
    cout << ". \n";
    cout << endl;

    savings = deposit(savings, paycheck);
    cout << "You now have ";
    print(savings);
    cout << " in your Savings account. \n";
    cout << endl;

    withdraw(checking, feeHBO);
    cout << "Withdrew ";
    print(feeHBO);
    cout << " for HBO Now,  you now have ";
    print(checking);
    cout << ". \n";
    cout << endl;

    accrue(RothIRA);
    cout << "You now have ";
    print(RothIRA);
    cout << " in your Roth IRA. \n";
    accrue(RothIRA);
    cout << "You now have ";
    print(RothIRA);
    cout << " in your Roth IRA. \n";
    cout << endl;

//A wild EXPENSE appeared!
    cout << "An unexpected expense appears! \n";
    print(unexpectedExpense);
    cout << endl;
    cout << "Attempting to withdraw from Savings. \n";
    withdraw(savings, unexpectedExpense);
    cout << "It's not very effective. \n";
    cout << "You now have ";
    print(savings);
    cout << " in your Savings account. \n";
    cout << endl;

    cout << "Attempting some bad withdraws and deposits. \n";
    deposit(checking, invalidAmount);
    withdraw(RothIRA, invalidAmount);

    return 0;
}

Account createAccount()
{
    Account newAccount;
//These will be used to convert Moneys into single number, and then back.
    double accountBalance;
    double cents;
    int dollars;

    cout << "Let's set up your account. \n";
    cout << "First, what's the name of the account? ";
    getline(cin, newAccount.accountName);
    cout << endl << endl;
    cout << "What is the interest rate of your " << newAccount.accountName << " account? ";
    cin >> newAccount.interest;
    cout << endl << endl;
    cout << "Finally, what is the starting balance of your " << newAccount.accountName << " account? $";
    cin >> accountBalance;
    cout << endl << endl;

    dollars = (int)accountBalance;
    cents = round((int)((accountBalance - dollars)*100));

    newAccount.balance.dollars = dollars;
    newAccount.balance.cents = cents;

    return newAccount;
}

Account deposit(Account account, Money deposit)
{
    if (deposit.dollars < 0 || deposit.cents < 0)
    {
        cout << "Cannot make negative deposit. \n";
        return account;
    }

//loop used to convert change into dollars
    while (deposit.cents > 99)
    {
        deposit.dollars++;
        deposit.cents -= 100;
    }

    account.balance.dollars += deposit.dollars;
    account.balance.cents += deposit.cents;
    
//loop used to convert change into dollars
    while (account.balance.cents > 99)
    {
        account.balance.dollars++;
        account.balance.cents -= 100;
    }

    cout << "$" << deposit.dollars << "." << deposit.cents << "0 deposited into " << account.accountName << ". \n";
    return account;
}

Money withdraw(Account &account, Money withdraw)
{
//will be used with overdrafting
    double difference;
    double balanceCombined;
    double withdrawCombined;

    if (withdraw.dollars < 0 || withdraw.cents < 0)
    {
        cout << "Cannot make negative withdrawl. \n";
        withdraw.dollars = 0;
        withdraw.cents = 0;
        cout << "$" << withdraw.dollars << "." << withdraw.cents << "0 withdrawn from  " << account.accountName << ". \n";
        return withdraw;
    }

    while (withdraw.cents > 99)
    {
        withdraw.dollars++;
        withdraw.cents -= 100;
    }


    if (account.balance.dollars - withdraw.dollars <= -50)
    {
    //converting Moneys into single numbers for operations, then breaking apart again
        balanceCombined = (account.balance.dollars + (account.balance.cents * 0.01));
        withdrawCombined = (withdraw.dollars + (withdraw.cents * 0.01));
    //taking in consideration the overcharge limit of 50
        difference = withdrawCombined - (balanceCombined - 50);

        withdraw.dollars = (int)difference;
        withdraw.cents = (int)((difference - withdraw.dollars) * 100);

    }
    
    
    account.balance.dollars -= withdraw.dollars;
    account.balance.cents -= withdraw.cents;

//Borrowing from 0
    if (account.balance.cents < 0)
    {
        account.balance.dollars--;
        account.balance.cents += 100;
    }

    cout << "$" << withdraw.dollars << "." << withdraw.cents << " withdrawn from  " << account.accountName << ". \n";
    return withdraw;
}

void accrue(Account &account)
{
    double balanceCombined;
    double interestAccrued;

//See comment above with related code section
    balanceCombined = (account.balance.dollars + (account.balance.cents * 0.01));
    interestAccrued = balanceCombined * account.interest;

    int dollars = (int)interestAccrued;
    int cents = (int)((interestAccrued - dollars) * 100);

    account.balance.dollars += dollars;
    account.balance.cents += cents;

    cout.precision(2);
    cout.setf(ios::fixed);

    cout << "At " << account.interest * 100 << "%, your " << account.accountName << " account earned $" << interestAccrued << ". \n";

}

void print(Account account)
{
    print(account.balance);
}

void print(Money money)
{
    double balanceCombined;

    balanceCombined = (money.dollars + (money.cents * 0.01));

    cout.precision(2);
    cout.setf(ios::fixed);

    if (balanceCombined < 0)
    {
        cout << "($" << abs(balanceCombined) << ")";
    }

    else
    {
        cout << "$" << balanceCombined;
    }
}


/*
    In hindsight I should have created a function to  convert the two separate 
    money forms into a single double as I used it so often, but time has cut me short.
    All in all the program was definitely a difficult refresher of what we learned 
    in CS211 and a good platform to build from.
*/
