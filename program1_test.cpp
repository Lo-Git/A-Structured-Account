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

//Function prototypes
Account createAccount();

Account deposit(Account account, Money deposit);

Money withdraw(Account &account, Money withdraw);

void accrue(Account &account);

void print(Account account);

void print(Money money);



int main()
{
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
    
    Account RothIRA = createAccount();
    RothIRA.balance.cents += 1;
    cout << "In your Roth IRA, you have ";
    print(RothIRA);
    cout << ". \n";
    cout << endl;

    deposit(savings, paycheck);
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

    if (deposit.cents > 100)
    {
        deposit.dollars++;
        deposit.cents -= 100;
    }

    account.balance.dollars += deposit.dollars;
    account.balance.cents += deposit.cents;


    if (account.balance.cents > 100)
    {
        account.balance.dollars++;
        account.balance.cents -= 100;
    }

    cout << "$" << deposit.dollars << "." << deposit.cents << "0 deposited into " << account.accountName << ". \n";
    print (account);
    return account;
}

Money withdraw(Account &account, Money withdraw)
{
    if (withdraw.dollars < 0 || withdraw.cents < 0)
    {
        cout << "Cannot make negative withdrawl. \n";
        withdraw.dollars = 0;
        withdraw.cents = 0;
        cout << "$" << withdraw.dollars << "." << withdraw.cents << "0 withdrawn from  " << account.accountName << ". \n";
        return withdraw;
    }

    if (withdraw.cents > 100)
    {
        withdraw.dollars++;
        withdraw.cents -= 100;
    }

    if (account.balance.dollars - withdraw.dollars < -50)
    {
        cout << "You don't have enough money. \n";
        withdraw.dollars = 0;
        withdraw.cents = 0;
        cout << "$" << withdraw.dollars << "." << withdraw.cents << "0 withdrawn from  " << account.accountName << ". \n";
        return withdraw;
    }
    
    if (account.balance.dollars - withdraw.dollars == -50 && withdraw.cents > 0)
    {
        cout << "You don't have enough money. \n";
        withdraw.dollars = 0;
        withdraw.cents = 0;
        cout << "$" << withdraw.dollars << "." << withdraw.cents << "0 withdrawn from  " << account.accountName << ". \n";
        return withdraw;
    }
    
    account.balance.dollars -= withdraw.dollars;
    account.balance.cents -= withdraw.cents;


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
