#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double activate(double x, int t) {
    switch (t) {
    case 1: 
        return x;
    case 2: 
        return x>=0 ?1 :0;
    case 3: 
        return x>=0 ?1 :-1;
    case 4: 
        return 1.0/(1.0 + exp(-x));
    case 5: 
        return 2.0/(1.0 + exp(-x)) - 1;
    case 6:
        if (x>1) return 1;
        if (x<0) return 0;
        return x;
    default: return x;
    }
}

void menu() {
    cout << "--- Activation Function ---\n";
    cout << "choose from the list:\n";
    cout << "1.Identity Function \n";
    cout << "2.Binary Function\n";
    cout << "3.Bipolar Function\n";
    cout << "4.Binary Sigmoid Function\n";
    cout << "5.Bipolar Sigmoid Function\n";
    cout << "6.Ramp Function\n";
}

int main() {
    int insize;
    cout << "enter the number of input cells: ";
    cin >> insize;

    vector<double> inputs;
    for (int i=0; i<insize;i++) {
        double val;
        cout<<"enter the input of cell "<<i+1<<" : ";
        cin>>val;
        inputs.push_back(val);
    }
    cout << "\t\t\t\t-------------------------------------------------\n";

    int hidden;
    cout<<"enter the number of hidden layers: ";
    cin>>hidden;

    vector<double>current=inputs;

    for (int l=1;l<=hidden;l++) {
        int cell;
        cout<<"enter the number of cells of layer "<<l<<" : ";
        cin>>cell;

	

        vector<vector<double>> weights(cell,vector<double>(current.size()));
        for (int n = 0;n <cell; n++) {
            for (int w=0; w<current.size(); w++) {
                cout<<"enter the weight for input "<< w+1 <<" in cell "<<n+1<<": ";
                cin>>weights[n][w];
            }
        }
        cout << "\t\t\t\t-------------------------------------------------\n";
        vector<double>outputs;
        for (int n=0;n<cell;n++) {
            double sum =0;
            for (int w =0;w<current.size();w++) {
                sum+=current[w]*weights[n][w];
            }
            outputs.push_back(sum); 
        }
        current=outputs;
    }

    cout<<"\n--- output layer ---\n";
    int outsize;
    cout<<"enter number of output neurons : ";
    cin>>outsize;

    vector<vector<double>>out_weights(outsize, vector<double>(current.size()));
    vector<double>f_output;

    for (int n=0;n<outsize;n++) {
        cout<<"enter weights for neuron "<<n+1<<"("<<current.size()<<" weights): ";
        for (int w=0; w < current.size(); w++) {
            cin>>out_weights[n][w];
        }
        double net_input =0;
        for (int w = 0; w < current.size(); w++) {
            net_input+= current[w]*out_weights[n][w];
        }
        cout << "net input to output neuron "<<n+1<< ": "<<net_input<< endl;

        f_output.push_back(net_input);
    }

    cout << "\t\t\t\t-------------------------------------------------\n";
    cout << "\n--- final output ---\n";
    for (double val:f_output) {
        cout<<val << " ";
    }
    cout<<endl;
    cout << "\n\t\t\t\t-------------------------------------------------\n";

    int c;
    while (true) {
		menu();
        cout << "enter your choice from 1 to 6: ";
		cin>>c;
		if (c>=1&&c<= 6) 
            break;
		cout << "invalid choice please try again\n";
    }

    cout <<"\n--- output with activation function ---\n";
    for (int i = 0;i<f_output.size();i++) {
        double active_val=activate(f_output[i],c);
        cout<<"Output " << i + 1 << ": " << active_val<< endl;
    }
    cout << "\t\t\t\t-------------------------------------------------\n";
    return 0;
}