#include <iostream>
#include<ostream>
#include<vector>
#include<map>
#include<string>
#include <algorithm>
#include <cctype>
#include<cmath>
#define ll long long int
using namespace std;
vector<int>v1(26);
map<ll,float>balance;
map<ll,float>::iterator itr;
map<ll,float>deposit_money;
map<ll,float>withdrawal_money;
map<ll,float>Minimum_repay_for_loan;
map<ll,ll>atm_no;
map<ll, map<string,float> >passbook;
map<ll, map<string,int> >trans_check;
ll temp_acc = 1;
ll temp_atm = 1000000000000000;
int temp_cvv = 100;

// User information
class User{
    public:
    string FirstName;
    string LastName;
    string Email;
    string Address;
    string PhoneNumber;
    string AccountType;
    int Age;
    ll CustomerId;
};
map<ll, User>Details;

// ATM Details
class AtmDetails{
    public:
    ll AtmNumber;
    string ExpiryDate;
    int CVV;
};
map<ll,AtmDetails> AtmCheck;



// Current month and year calculation
time_t now = time(0);
tm *ltm = localtime(&now);
int curr_year = 1900 + ltm->tm_year;
int curr_month = 1+ ltm->tm_mon;
string  curr_time = to_string(curr_month) + "/" + to_string(curr_year);





// Saving  Account
class SavingAccount{
    // string name, address, email;
    public:
    void OpenAccount(){
        float start_deposit;
        cout<<"Minimum amount to be deposited is 10000:\n";
        cout<<"Enter how much money you want to deposit: \n";
        cin>>start_deposit;
        while(start_deposit < 10000){
            cout<<"minimum amount to open account is 10000: \n";
            float temp;
            cout<<"enter deposit money : ";
            cin>>temp;
            start_deposit = temp;
        }
        balance[temp_acc] = start_deposit;
        deposit_money[temp_acc] = start_deposit;
        cout<<"Your ATM number is: "<<" "<<temp_atm<<"\n";
        cout<<"ATM CVV is :"<<" "<<temp_cvv<<"\n";
        string ExpiryDate = to_string(curr_month) + "/" + to_string(curr_year+5);
        cout<<"ATM expiry date :"<<" "<<ExpiryDate<<"\n";

        AtmDetails a1;
        a1.AtmNumber = temp_atm;
        a1.CVV = temp_cvv;
        a1.ExpiryDate = ExpiryDate;
        AtmCheck[temp_acc] = a1;

        atm_no[temp_atm] = temp_acc;
        passbook[temp_acc][curr_time] = start_deposit;
        temp_acc++;
        temp_atm++;
        temp_cvv++;
    }
    
    void Deposit(ll AccountNumber){
        
        float amount;
        cout<<"\nEnter amount you want to deposit :";
        cin>>amount;
        balance[AccountNumber] += amount;
        deposit_money[AccountNumber] += amount;
        passbook[AccountNumber][curr_time] += amount;

        cout<<"\nYour account balance is: "<<balance[AccountNumber];
    }
     
    void DirectWithdraw(ll AccountNumber){
        float amount;
        cout<<"\nEnter amount you want to withdraw :";
        cin>>amount;
        if(withdrawal_money[AccountNumber] + amount > 50000){
            cout<<"\nYou can't withdraw more then 50000 in a day.";

        }
        else if(balance[AccountNumber] - amount < 0){
            cout<<"insufficient balance.\n";
        }
        else{
            balance[AccountNumber] -= amount;
            withdrawal_money[AccountNumber] += amount;
            passbook[AccountNumber][curr_time] -= amount;
            cout<<"\nYour account balance is: "<<balance[AccountNumber];
        }
        
    }
    
    void AtmWithdraw(ll AccountNumber){
        float amount;
        cout<<"Enter amount you want to withdraw :";
        cin>>amount;
        if(balance[AccountNumber] - amount < 0){
            cout<<"insufficient balance.\n";
        }
        else{
            balance[AccountNumber] -= amount;
            withdrawal_money[AccountNumber] += amount;
            passbook[AccountNumber][curr_time] -= amount;
            trans_check[AccountNumber][curr_time]++;
            if(trans_check[AccountNumber][curr_time] > 5){
                balance[AccountNumber] -= 500;
                passbook[AccountNumber][curr_time] -= 500;
            }
            cout<<"\nYour account balance is: "<<balance[AccountNumber];
        }
        
    }

};




// Current Account
class CurrentAccount{
    public:
    void OpenAccount(){
        float start_deposit;
        cout<<"Minimum amount to be deposited is 100000:\n";
        cout<<"Enter how much money you want to deposit: \n";
        cin>>start_deposit;
        while(start_deposit < 100000){
            cout<<"minimum amount to open account is 100000: \n";
            float temp;
            cout<<"enter deposit money : ";
            cin>>temp;
            start_deposit = temp;
        }
        balance[temp_acc] = start_deposit;
        deposit_money[temp_acc] = start_deposit;
        cout<<"Your ATM number is: "<<" "<<temp_atm<<"\n";
        cout<<"ATM CVV is :"<<" "<<temp_cvv<<"\n";
        string ExpiryDate = to_string(curr_month) + "/" + to_string(curr_year+5);
        cout<<"ATM expiry date :"<<" "<<ExpiryDate<<"\n";

        AtmDetails a1;
        a1.AtmNumber = temp_atm;
        a1.CVV = temp_cvv;
        a1.ExpiryDate = ExpiryDate;
        AtmCheck[temp_acc] = a1;


        atm_no[temp_atm] = temp_acc;
        passbook[temp_acc][curr_time] = start_deposit;
        temp_acc++;
        temp_atm++;
        temp_cvv++;
    }
    
    void Deposit(ll AccountNumber){
        float amount;
        cout<<"\nEnter amount you want to deposit :";
        cin>>amount;
        balance[AccountNumber] += amount;
        deposit_money[AccountNumber] += amount;
        passbook[AccountNumber][curr_time] += amount;
        cout<<"\nYour account balance is: "<<balance[AccountNumber];
    }
     
    void DirectWithdraw(ll AccountNumber){
        float amount;
        cout<<"\nEnter amount you want to withdraw :";
        cin>>amount;
        if(balance[AccountNumber] - amount < 0){
            cout<<"insufficient balance.\n";
        }
        else{
            float charge = 0.005*amount;
            amount += charge;
            balance[AccountNumber] -= amount;
            passbook[AccountNumber][curr_time] -= amount;
            cout<<"\nYour account balance is: "<<balance[AccountNumber];
        }
        

    }
    
    void AtmWithdraw(ll AccountNumber){
        
        float amount;
        cout<<"\nEnter amount you want to withdraw :";
        cin>>amount;

        
        if(balance[AccountNumber] - amount < 0){
            cout<<"insufficient balance.\n";
        }
        else{
            float charge = 0.005*amount;
            amount += charge;
            balance[AccountNumber] -= amount;
            passbook[AccountNumber][curr_time] -= amount;
            cout<<"\nYour account balance is: "<<balance[AccountNumber];
        }
        
    }

};



// Loan Account
class LoanAccount{
    public:
    void OpenAccount(){
        ll ExistingAccountNumber;
        cout<<"Enter your existing account number  in this bank saving/current account; ";
        cin>>ExistingAccountNumber;
        int x =1;
        for(itr =balance.begin(); itr != balance.end(); itr++){
            if(itr->first == ExistingAccountNumber){
                x = 2;
            }
        }
        if(x == 1){
            cout<<"You have enter wrong account number.\nThank you!\n1";

            return;
        }
        User temporary;
        temporary = Details[ExistingAccountNumber];
        if(temporary.Age < 25){
            cout<<"\nSorry minimum age required to get loan is 25";
            return;
        }
        if(deposit_money[ExistingAccountNumber] < (5000000/4)){
            cout<<"\nSorry you can't take a loan because of 40% deposited criteria and a minimum loan amount 500000. ";
            return;
        }
        cout<<"\nplease confirm your details:";
        cout<<"\nYour first name: "<<temporary.FirstName;
        cout<<"\nYour last name: "<<temporary.LastName;
        cout<<"\nYour address: "<<temporary.Address;
        cout<<"\nYour email: "<<temporary.Email;
        cout<<"\nYour phone number: "<<temporary.PhoneNumber;
        cout<<"\nYour age: "<<temporary.Age;
        cout<<"\nYour customer id: "<<temporary.CustomerId;
        cout<<"\nyour account type is: "<<temporary.AccountType;

        cout<<"\n\nSelect an option: ";
        cout<<"\n\n1.Proceed for Loan.";
        cout<<"\n2.Account details is wrong.\n";
        int z;
        cin>>z;
        if(z== 1){
            cout<<"\nMinimum duration of loan account will be 2 years."
            <<"\n"<<"Minimum amount to take a loan is 5,00,000"<<"\n";
            cout<<"Please select loan type: \n";
            cout<<"1. Home loan\n";
            cout<<"2. Car loan \n";
            cout<<"3. Personal loan\n";
            cout<<"4. Business loan \n";
            
            int x;
            cin>>x;
            float loan_amount;
            int loan_duration;
            cout<<"\nPlease enter the loan amount: ";
            cin>>loan_amount;
            while(loan_amount < 500000){
                cout<<"\nminimum loan amount is 5,00,000: \n";
                float temp;
                cout<<"enter loan amount again : ";
                cin>>temp;
                loan_amount = temp;
            }
            Minimum_repay_for_loan[temp_acc] = 0.1*loan_amount;
            cout<<"\nPlease enter the loan duration: ";
            cin>>loan_duration;
            cout<<"\n";
            while(loan_duration < 2){
                cout<<"minimum loan duration is 2: \n";
                int temp;
                cout<<"enter loan duration again : ";
                cin>>temp;
                loan_amount = temp;
            }
            
            if(loan_amount > 0.4*deposit_money[ExistingAccountNumber]){
                cout<<"\nSorry bank can only give 40% of total deposited money";
                return;
            }
            cout<<"Your loan account number is: "<<" "<<temp_acc<<"\n";
            passbook[temp_acc][curr_time] = 0;
            if(x == 1){
                float amount_to_be_paid = loan_amount * (pow(1 + 0.07/2,2*loan_duration));
                balance[temp_acc] = amount_to_be_paid;
            }
            else if(x == 2){
                float amount_to_be_paid = loan_amount * (pow(1 + 0.08/2,2*loan_duration));
                balance[temp_acc] = amount_to_be_paid;
            }
            else if(x == 3){
                float amount_to_be_paid = loan_amount * (pow(1 + 0.12/2,2*loan_duration));
                balance[temp_acc] = amount_to_be_paid;
            }
            else{
                float amount_to_be_paid = loan_amount * (pow(1 + 0.15/2,2*loan_duration));
                balance[temp_acc] = amount_to_be_paid;
            }
            User open;
            open.AccountType = "LOAN ACCOUNT";
            open.Address = temporary.Address;
            open.Age = temporary.Age;
            open.CustomerId = temporary.CustomerId + 1;
            open.Email = temporary.Email;
            open.FirstName = temporary.FirstName;
            open.LastName = temporary.LastName;
            open.PhoneNumber = temporary.PhoneNumber;

            Details[temp_acc] = open;
            
            temp_acc++;
        }
        
    }

    void Deposit(ll AccountNumber){
        float amount;
        cout<<"\nEnter amount you want to deposit :";
        cin>>amount;
        if(Minimum_repay_for_loan[AccountNumber] < amount){
            cout<<"\ndepositing amount should not exceed 10% of total loan amount.";
            return;
        }
        if(balance[AccountNumber] - amount < 0){
            cout<<"\nYou are depositing greater than your total loan amount";
            return;
        }
        balance[AccountNumber] -= amount;
        passbook[AccountNumber][curr_time] += amount;

        cout<<"\n Toatl loan amount you have paid is: "<<passbook[AccountNumber][curr_time];
        cout<<"\n Total loan amount to be paid is: "<<balance[AccountNumber];
    }
    

};



// Start function
void Start(){
    cout<<"Welcome to our bank.\n";
    cout<<"Please select an option:\n";
    cout<<"1.Open Account\n";
    cout<<"2.Deposit\n";
    cout<<"3.Direct Withdrawal\n";
    cout<<"4.ATM Withdrawal\n";
    cout<<"5.check balance\n";
    cout<<"6.Loan\n";

    int x;
    cin>>x;


    // for opening account 
    if(x == 1){
        User u1;
        cout<<"Enter your first name: ";
        cin>>u1.FirstName;
        cout<<"\nEnter your last name: ";
        cin>>u1.LastName;
        cout<<"\nEnter your email: ";
        cin>>u1.Email;
        cout<<"\nEnter your Address: ";
        cin>>u1.Address;
        cout<<"\nEnter your phone number: ";
        string x;
        cin>>x;
        while(x.length() != 10){
            string temp;
            cout<<"\nEnter your correct phone number: ";
            cin>>temp;
            x = temp;
        }
        u1.Address = x;
        cout<<"\nEnter your age: ";
        cin>>u1.Age;
        ll customer_id = 0;
        string name = u1.FirstName;
        int name_len = name.size();
        transform(name.begin(), name.end(), name.begin(), ::toupper);
        for(int i=0; i<name_len; i++){
            customer_id += v1[name[i] - 'A'];
        }
        u1.CustomerId = customer_id;

        cout<<"Please select account type:\n";
        cout<<"1. Saving Account\n";
        cout<<"2. Current Account\n";

        int y;
        cin>>y;
        cout<<"Your account number is: "<<" "<<temp_acc<<"\n";
        
        if(y == 1){
            u1.AccountType = "SAVING ACCOUNT";
            Details[temp_acc] = u1;
            SavingAccount open;
            open.OpenAccount();
        }
        else{
            if(u1.Age <18){
                cout<<"\nSorry minimum age required for opening current account is 18.";
            }
            else{
                u1.AccountType = "CURRENT ACCOUNT";
                Details[temp_acc] = u1;
                CurrentAccount open;
                open.OpenAccount();
            }
            
        }
        





    }

    // for deposit 
    else if(x == 2){

        ll AccountNumber;
        cout<<"\nEnter your account no. :";
        cin>>AccountNumber;

        int x =1;
        for(itr =balance.begin(); itr != balance.end(); itr++){
            if(itr->first == AccountNumber){
                x = 2;
            }
        }
        if(x == 1){
            cout<<"You have enter wrong account number.\nThank you!\n1";
        }

        else{
            User temporary;
            temporary = Details[AccountNumber];
            cout<<"\nplease confirm your details:";
            cout<<"\nYour first name: "<<temporary.FirstName;
            cout<<"\nYour last name: "<<temporary.LastName;
            cout<<"\nYour address: "<<temporary.Address;
            cout<<"\nYour email: "<<temporary.Email;
            cout<<"\nYour phone number: "<<temporary.PhoneNumber;
            cout<<"\nYour age: "<<temporary.Age;
            cout<<"\nYour customer id: "<<temporary.CustomerId;
            cout<<"\nyour account type is: "<<temporary.AccountType;

            cout<<"\n\nSelect an option: ";
            cout<<"\n\n1.Proceed for deposit.";
            cout<<"\n2.Account details is wrong.\n";
            int z;
            cin>>z;
            if(z == 1){
                if(temporary.AccountType == "SAVING ACCOUNT"){
                    SavingAccount deposite;
                    deposite.Deposit(AccountNumber);
                }
                else if(temporary.AccountType == "CURRENT ACCOUNT"){
                    CurrentAccount deposite;
                    deposite.Deposit(AccountNumber);
                }
                else{
                    LoanAccount deposite;
                    deposite.Deposit(AccountNumber);
                }

            }
        }
        
    }

    // for passbook direct withdrawal
    else if(x == 3){

        ll AccountNumber;
        cout<<"\nEnter your account no. :";
        cin>>AccountNumber;

        int x =1;
        for(itr =balance.begin(); itr != balance.end(); itr++){
            if(itr->first == AccountNumber){
                x = 2;
            }
        }
        if(x == 1){
            cout<<"You have enter wrong account number.\nThank you!\n1";
        }
        else{
            User temporary;
            temporary = Details[AccountNumber];
            cout<<"\nplease confirm your details:";
            cout<<"\nYour first name: "<<temporary.FirstName;
            cout<<"\nYour last name: "<<temporary.LastName;
            cout<<"\nYour address: "<<temporary.Address;
            cout<<"\nYour email: "<<temporary.Email;
            cout<<"\nYour phone number: "<<temporary.PhoneNumber;
            cout<<"\nYour age: "<<temporary.Age;
            cout<<"\nYour customer id: "<<temporary.CustomerId;
            cout<<"\nyour account type is: "<<temporary.AccountType;

            cout<<"\n\nSelect an option: ";
            cout<<"\n\n1.Proceed for direct withdrawal.";
            cout<<"\n2.Account details is wrong.\n";
            int z;
            cin>>z;
            
            if(z == 1){
                if(temporary.AccountType == "SAVING ACCOUNT"){
                    SavingAccount withdraw;
                    withdraw.DirectWithdraw(AccountNumber);
                }
                else if(temporary.AccountType == "CURRENT ACCOUNT"){
                    CurrentAccount withdraw;
                    withdraw.DirectWithdraw(AccountNumber);
                }
            }
        }


        
    }

    // for atm withdrawal
    else if(x == 4){
        ll ATMNumber;
        int cvv;
        string ExpiryDate;
        cout<<"\nEnter your ATM number. :";
        cin>>ATMNumber;
        cout<<"\nEnter your Expiry date in MM/YYYY format: ";
        cin>>ExpiryDate;
        cout<<"\nEnter your cvv: ";
        cin>>cvv;
         
        
        ll AccountNumber = atm_no[ATMNumber];
        AtmDetails A1 = AtmCheck[AccountNumber];
        
        if(A1.CVV != cvv || A1.ExpiryDate != ExpiryDate){
            cout<<"\nplease enter the correct details";
        }

        else{
            User temporary;
            temporary = Details[AccountNumber];
            cout<<"\nplease confirm your details:";
            cout<<"\nYour first name: "<<temporary.FirstName;
            cout<<"\nYour last name: "<<temporary.LastName;
            cout<<"\nYour address: "<<temporary.Address;
            cout<<"\nYour email: "<<temporary.Email;
            cout<<"\nYour phone number: "<<temporary.PhoneNumber;
            cout<<"\nYour age: "<<temporary.Age;
            cout<<"\nYour customer id: "<<temporary.CustomerId;
            cout<<"\nyour account type is: "<<temporary.AccountType;

            cout<<"\n\nSelect an option: ";
            cout<<"\n\n1.Proceed for atm  withdrawal.";
            cout<<"\n2.Account details is wrong.\n";
            int z;
            cin>>z;

            if(z == 1){
                if(temporary.AccountType == "SAVING ACCOUNT"){
                    SavingAccount atmwithdraw;
                    atmwithdraw.AtmWithdraw(AccountNumber);
                }
                else if(temporary.AccountType == "CURRENT ACCOUNT"){
                    CurrentAccount atmwithdraw;
                    atmwithdraw.AtmWithdraw(AccountNumber);
                }
            }
        }

        
    }
    else if(x == 5){
        ll AccountNumber;
        cout<<"please enter the account no.:";
        cin>>AccountNumber;

        int x =1;
        for(itr =balance.begin(); itr != balance.end(); itr++){
            if(itr->first == AccountNumber){
                x = 2;
            }
        }
        if(x == 1){
            cout<<"You have enter wrong account number.\nThank you!\n";
        }
        else{
            User temporary;
            temporary = Details[AccountNumber];
            cout<<"\nYour customer id: "<<temporary.CustomerId;
            cout<<"\nyour account type is: "<<temporary.AccountType;


            cout<<"\nYour account balance is : ";
            cout<<balance[AccountNumber]<<"\n";
        }

        
    }
    else if(x == 6){
        LoanAccount open;
        open.OpenAccount();
    }
    else{
        cout<<"you have select wrong number";
    }


    cout<<"\nYou want to exit press 1 else 2\n";
    int z;
    cin>>z;
    if(z == 2){
        Start();
    }

}


int main() {

    v1[0] = 1;
    int a = 1;
    for(int i=1; i<26; i++){
        v1[i] = a*2 + i+1;
        a = v1[i];
    }

    Start();

    return 0;
}