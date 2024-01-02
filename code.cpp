#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <sstream>


using namespace std;

// const string SKIPPED = "laiefublaefawefamefnlawefo";

void tolower_string(string& x) {
    for (char& c : x) {
        c = tolower(c);     
    }
}
int ischaracter(string x) {
    return x.length() == 1 && isalpha(x[0]);
}
void space_between() {
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------------------------------------------------\n";
}
void error_wrong_command() {
    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n---------------------------------------------  ERROR   ---------------------------------------------\n\n";
}
void new_screen () {
    int num_lines = 100;
    for (int i = 0; i < num_lines; i ++) {
        cout<<'\n';
    }
}
void press_something() {
    cout<<"\n\n\n(Press anything to continue)";
    fflush(stdin);
    getchar();
}
string name_element_from_flow(int element_index) {
    switch (element_index)
    {
    case 1:
        return "TITLE";
        break;
    case 2:
        return "TEXT";
    case 3:
        return "TEXT INPUT";
    case 4:
        return "NUMBER INPUT";
    case 5:
        return "CALCULUS";
    case 6:
        return "DISPLAY";
    case 7:
        return "TEXT FILE";
    case 8:
        return "CSV FILE";
    case 9:
        return "OUTPUT";
    default:
        return "ERROR";
        break;
    }
}

string trim(const std::string& str) {
    // Find the first non-space character
    size_t first = str.find_first_not_of(' ');

    // If the string is all spaces, return an empty string
    if (first == std::string::npos) {
        return "";
    }

    // Find the last non-space character
    size_t last = str.find_last_not_of(' ');

    // Extract the substring between the first and last non-space characters
    return str.substr(first, last - first + 1);
}

class Interface {
    private:
    bool skipped = false;
    public:
    virtual void set_output (ofstream& fout) {}
    virtual void get_display(string* x, string* y) {}
    // virtual void input_data() {}
    virtual void execution() {}
    virtual string get_name() {
        return "";
    }

    // for number_input
    // chiar nu am stiut cum sa rezolv problema. Nu ma lasa sa apelez gen_input daca apelam ca si element al vectorului pentru ca nu era functie definita in Interface
    virtual float get_number_input() {
        return 0;
    }
    virtual void get_the_flow(vector<shared_ptr<Interface>> flow_input) {}

    // for text_file input
    virtual string get_path_to_file() {
        return "";
    }

    // Fiecare optiune va avea o functie de setare si verificare de skipped, pentru posibilitatea utilizatorului de a sari peste un pas atunci cand este in flow
    void set_skipped() {
        while (true) {
            cout<<"Do you want to continue this step? (y/n): ";
            fflush(stdin);
            string decision;
            getline(cin, decision);
            decision =trim(decision);
            tolower_string(decision);
            if (decision == "n") {
                skipped = true;
                return;
            } else if( decision != "y") {
                error_wrong_command();
                cout<<"Possible commands: y for yes, or n for no.\n";
            } else {
                return;
            }
        }
    }
    bool is_skipped() {
        return skipped;
    }
};

// STEP 1
class Title : public Interface{
    private:
    string name_class = "Title";
    string title, subtitle = "";
    public:
    string get_name() override {
        return name_class;
    }

    void execution() override {
        // space_between();
        cout<<"\n- Title -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        }
        cout<<"Give a title: ";
        fflush(stdin);
        getline(cin, title);
        title = trim(title);

        cout<<"\nGive a subtitle (optional):";
        fflush(stdin);
        getline(cin, subtitle);
        subtitle = trim(subtitle);
    }
    void set_output(ofstream& fout) override {
        fout<<"\t\t\t"<<title;
        if (subtitle != "") {
            fout<<"\n\n"<<subtitle<<"\n";

        }
    }
};

// STEP 3
class Text_input : public Interface {
    private:
    string name_class = "Text input";
    string description = "", text = "";

    public:
    string get_name() override {
        return name_class;
    }
    void execution() override {
        cout<<"- Text input -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        }
        cout<<"Give a description of the text: ";
        fflush(stdin);
        getline(cin, description);
        description = trim(description);

        cout<<"Give a text: \n";
        fflush(stdin);
        getline(cin, text);
        text = trim(text);
    }
    void set_output(ofstream& fout) override {
        if (description != "") {
            fout<<"\n"<<"(Desciption: "<<description<<").\n";
        }
        fout<<text<<endl;   
    }
};

// STEP 4
class Number_input : public Interface {
    private:

    float number_input;
    string input_unchecked,description = "", name_class = "Number input";
    
    public:
    string get_name() override {
        return name_class;
    }
    float get_number_input() override {
        return number_input;
    }
    void set_output(ofstream& fout) override {
        if (description != "") {
            fout<<"Description: "<<description<<endl;
        }
        fout<<"Number: "<<number_input<<endl;
    }

    void execution() override {
        cout<<"- Number input -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        } 
        cout<<"Give description:";
        fflush(stdin);
        getline(cin,  description);
        description = trim(description);

        while (true) {
            cout<<"Give a number: ";
            fflush(stdin);
            getline(cin,  input_unchecked);
            input_unchecked = trim(input_unchecked);
            if (all_of(input_unchecked.begin(), input_unchecked.end(), [](char c) {
                return std::isdigit(c) || c == '.';
            }) && std::count(input_unchecked.begin(), input_unchecked.end(), '.') <= 1) {
                number_input =stof(input_unchecked); // Convert string to float
                cout<<get_number_input()<<endl;
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid number." << std::endl;
            }
        }
    }
};

// STEP 5
class Calculus : public Interface {
    private:
    int pozition1, pozition2;
    float result;
    vector<shared_ptr<Interface>> flow;
    string name_class = "Calculus", operation, pozition1_string, pozition2_string;

    public:
    string get_name() override {
        return name_class;
    }
    void get_the_flow(vector<shared_ptr<Interface>> flow_input) override{
        this->flow = flow_input;
    }
    void set_output(ofstream& fout) override {
        fout<<"Result: "<<result<<endl;   
    }
    void execution() override {
        cout<<"- Calculus -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        } 
        // get and verify the values given
        // first input
        bool ok = true;
        while (true) {
            if (ok == false) {
                set_skipped();
                if (is_skipped()) {
                    return;
                }       
            }
            ok = false;
            cout<<"Give the previous step that you want to include in a calculus: ";
            fflush(stdin);
            getline(cin, pozition1_string);
            pozition1_string = trim(pozition1_string);
            if (all_of(pozition1_string.begin(), pozition1_string.end(), ::isdigit)) {
                pozition1 = stoi(pozition1_string);
                if (flow.size() >= pozition1 && flow[pozition1 - 1]->get_name() == "Number input") {
                    if (!flow[pozition1 - 1]->is_skipped()) {
                        break;
                    } else {
                        error_wrong_command();
                        cout<<"Step skipped!\n";
                    }
                } else {

                    error_wrong_command();
                    cout<< "Not an \"Number input\" or out of limit!!!\n";
                }
            } else {
                error_wrong_command();
                cout<<"Not a number\n";
            }
        }

        // second input
        ok = true;
        while (true) {
            if (ok == false) {
                set_skipped();
                if (is_skipped()) {
                    return;
                }       
            }
            ok = false;
            cout<<"Give the next step: ";
            fflush(stdin);
            getline(cin, pozition2_string);
            pozition2_string = trim(pozition2_string);
            // cin.ignore();
            if (all_of(pozition2_string.begin(), pozition2_string.end(), ::isdigit)) {
                pozition2 = stoi(pozition2_string);
                if (flow.size() >= pozition2 && flow[pozition2 - 1]->get_name() == "Number input") {
                    if (!flow[pozition2 - 1]->is_skipped()) {
                        break;
                    } else {
                        error_wrong_command();
                        cout<<"Step skipped!\n";
                    }
                } else {
                    error_wrong_command();
                    cout<< "Not an \"Number input\" or out of limit!!!\n";
                }
            } else {
                error_wrong_command();
                cout<<"Not a number\n";
            }
        }

        // get operation
        cout<<"Give operation:";
        fflush(stdin);
        getline(cin, operation);
        operation = trim(operation);
        if (operation.length() == 1 ) {
            switch (operation[0]) {
                case '*':
                {
                    result = flow[pozition1 - 1]->get_number_input() * flow[pozition2 - 1]->get_number_input();
                    break;
                }
                case '/':
                {
                    result = flow[pozition1 - 1]->get_number_input() / flow[pozition2 - 1]->get_number_input();
                    break;
                }
                case '\\':
                {
                    result = flow[pozition1 - 1]->get_number_input() / flow[pozition2 - 1]->get_number_input();
                    break;
                }
                case '+':
                {
                    result = flow[pozition1 - 1]->get_number_input() + flow[pozition2 - 1]->get_number_input();
                    break;
                }
                case '-':
                {
                    result = flow[pozition1 - 1]->get_number_input() - flow[pozition2 - 1]->get_number_input();
                    break;
                }
                default:
                {
                    error_wrong_command();
                    cout<<"\n\nNot valid sign!!\n\n";
                    break;
                }
            }
        } else if (operation.length() == 3) {
            tolower_string(operation);
            if (operation == "min") {
                result = min(flow[pozition1 - 1]->get_number_input(), flow[pozition2 - 1]->get_number_input());
            } else if (operation == "max") {
                result = max(flow[pozition1 - 1]->get_number_input(), flow[pozition2 - 1]->get_number_input());
            } else {
                error_wrong_command();
                cout<<"Not a valid command!!n";
            }
        } else {
            error_wrong_command();
            cout<<"Not a valid command!!!\n";
        }
        cout<<"RESOLT: "<< result<<"\n";
        press_something();
        space_between();
    }
};

// STEP 6
class Display : public Interface {
    private:
    string command, name_class = "Display";
    int command_step;
    vector<shared_ptr<Interface>> flow;

    public:
    string get_name() override {
        return name_class;
    }
    void get_the_flow(vector<shared_ptr<Interface>> flow_input) override {
        flow = flow_input;
    }

    void execution() override {

        cout<<"- Display -\n";
        
        bool ok = true;
        while (ok == true) {
            set_skipped();
            if (is_skipped()) {
                return;
            }

            cout<<"Give the previous step that you want to display in treminal: ";
            fflush(stdin);
            getline(cin, command);
            command = trim(command);
            ok == false;
            if (all_of(command.begin(), command.end(), ::isdigit)) {
            command_step = stoi(command);
            if (flow.size() >= command_step) {
                cout<<"\n\n";
                if (flow[command_step - 1]->get_name() == "Text file") {
                    if (flow[command_step - 1]->is_skipped()) {
                        error_wrong_command();
                        cout<<"Text file skipped!\n\n";
                    } else {
                        // Afisam tot continutul din fisier
                        string description, file_path;
                        flow[command_step - 1]->get_display(&description, &file_path);
                        ifstream fin (file_path.c_str());

                        if (fin.is_open()) {
                            cout << "File Contents:\n";
                            string line;
                            while (getline(fin, line)) {
                                cout << line << endl;
                            }
                            fin.close();
                        } else {
                            cout << "Unable to open file: " << file_path << endl;
                        }
                        break;
                    }
                    
                } else if (flow[command_step - 1]->get_name() == "CSV file") {
                    if (flow[command_step - 1]->is_skipped()) {
                        error_wrong_command();
                        cout<<"CSV file skipped!\n\n";
                    } else {

                        // Afisam tot CSV ul
                        string description, file_path;
                        flow[command_step - 1]->get_display(&description, &file_path);
                        ifstream fin (file_path.c_str());
                        if (fin.is_open()) {
                            cout << "CSV File Contents:\n";
                            
                            string line;
                            while (getline(fin, line)) {
                                std::istringstream ss(line);
                                vector<string> tokens;

                                while (getline(ss, line, ',')) {
                                    tokens.push_back(line);
                                }

                                // Display the CSV values
                                for (const auto& token : tokens) {
                                    cout << token << "\t";
                                }

                                cout << std::endl;
                            }

                            fin.close();
                        } else {
                            std::cerr << "Unable to open file: " << file_path << std::endl;
                        }
                        break;
                    }
                } else {
                    error_wrong_command();
                    cout<<"\n\tSomething went wrong; the step was not identified correctly!! (The display can only show txt or csv content. to see the content, please enter the step that contains information about the txt or csv file.)\n\n";
                    ok = true;
                }

            } else {
                cout<<"NOT A VALID INPUT!!\n\n";
                ok = true;
            }
            }
        }
        press_something();
        space_between();
    }
};

// STEP 7
class Text_file_input : public Interface {
    private:
    string path_to_folder = "files";
    string file_name, path_to_file, name_class = "Text file";
    string description = "";
    public:
    
    string get_name() override {
        return name_class;
    }

    void get_display(string* description, string* file_path) override{
        *description = this->description;
        *file_path = this->path_to_file;
    }
    void set_output(ofstream& fout) override {
           if (description != "") {
            fout<<"Description: "<<description<<endl;
           }
           fout<<"File name: "<<file_name<<endl;
    }

    void execution() override {
        cout <<"- Text file -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        } 
        if (path_to_file == "") {
            cout<<"Introduceti descrierea: ";
            fflush(stdin);
            getline(cin, description);
            description = trim(description);

            bool ok = true;
            while (path_to_file == "") {
                if (ok == false) {
                    set_skipped();
                    if (is_skipped()) {
                        return;
                    }
                }
                ok = false;
                cout<<"Introduceti numele fisierului (case sensitive; introduceti si tipul fisierului - .txt): ";
                fflush(stdin);
                getline(cin, file_name);
                file_name = trim(file_name);
                if (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".txt") {
                    error_wrong_command();
                    cout<<"\tNot a .txt file!!\n";
                } else {
                    path_to_file = path_to_folder + "/" + file_name;
                    try
                    {
                        ifstream file_in(path_to_file.c_str());
                        if (!file_in.good()) {
                            throw std::runtime_error("File not found or cannot be opened");
                        } else {
                            cout<<"worked!\n\n";
                        }
                        file_in.close();
                    }
                    catch(const std::runtime_error& e)
                    {
                        std::cerr << "\n\n\nError: " << e.what() << "\n\n";
                        path_to_file = "";
                        file_name = "";
                        description = "";
                    }
                }
            }
        }
    }
    string get_path_to_file() override {
        return path_to_file;
    }
};

// STEP 8 - e exact acelasi lucru
class CSV_file_input : public Interface {
    private:
    string path_to_folder = "files";
    string file_name, path_to_file, name_class = "CSV file";
    string description = "";
    public:
    
    string get_name() override {
        return name_class;
    }
    void get_display(string* description, string* file_path) override{
        *description = this->description;
        *file_path = this->path_to_file;
    }
        void set_output(ofstream& fout) override {
           if (description != "") {
            fout<<"Description: "<<description<<endl;
           }
           fout<<"File name: "<<file_name<<endl;
    }

    void execution() override {
        cout<<"- CSV file -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        } 
        if (path_to_file == "") {
            cout<<"Introduceti descrierea: ";
            fflush(stdin);
            getline(cin, description);
            description = trim(description);

            bool ok = true;
            while (path_to_file == "") {
                if (ok == false) {
                    set_skipped();
                    if (is_skipped()) {
                        return;
                    }           
                }
                ok = false;
                cout<<"Introduceti numele fisierului (case sensitive; introduceti si tipul fisierului - .csv): ";
                fflush(stdin);
                getline(cin, file_name);
                file_name = trim(file_name);
                if (file_name.length() < 4 || file_name.substr(file_name.length() - 4) != ".csv") {
                    error_wrong_command();
                    cout<<"\tNot a .csv file!!\n";
                } else {
                    path_to_file = path_to_folder + "/" + file_name;
                    try
                    {
                        ifstream file_in(path_to_file.c_str());
                        if (!file_in.good()) {
                            throw std::runtime_error("File not found or cannot be opened");
                        } else {
                            cout<<"worked!\n\n";
                        }
                        file_in.close();
                    }
                    catch(const std::runtime_error& e)
                    {
                        std::cerr << "\n\n\nError: " << e.what() << "\n\n";
                        path_to_file = "";
                        file_name = "";
                    }
                }
            }
        }
    }
    string get_path_to_file() override {
        return path_to_file;
    }
};

// STEP 9
class Output : public Interface {
    private:
    string new_file_name, name_class = "Output", command;
    int step;
    vector<shared_ptr<Interface>>  flow;

    public:

    void get_the_flow(vector<shared_ptr<Interface>> flow_input) override {
        this->flow = flow_input;
    } 
    void execution() override {
        cout<<"- Output -\n";
        set_skipped();
        if (is_skipped()) {
            return;
        }
        cout<<"Provide the name of the file what will be created (no extension): ";
        fflush(stdin);
        cin>>new_file_name;
        new_file_name = "files/" + new_file_name + ".txt";
        
        ofstream fout(new_file_name.c_str());

        if (!fout.is_open()) {
            cout<<"\n\nSomething went wrong!\n";
            return;
        }
        while (true) {
            cout<<"Enter the previous steps you want to add or e to esc (one by one; they will be in the same order as you entered them): ";
            fflush(stdin);
            getline(cin, command);
            command = trim(command);
            if (ischaracter(command)) {
                tolower_string(command);
                if (command == "e") {
                    break;
                } else {
                    error_wrong_command();
                }
            } else if (all_of(command.begin(), command.end(), ::isdigit)) {
                step = stoi(command);
                if (step <= flow.size() && flow[step - 1]->is_skipped() == false) {
                    flow[step - 1]->set_output(fout);
                } else {
                    error_wrong_command();
                }
            }else {
                error_wrong_command();
            }
        }
        fout.close();
    }
};
class Menu {
    private:

    // matricea de flow uri si vectorul de flow uri ce ulterior va fii pus in matrice sunt de tip int, iar matricea de informatii este de tip Interface
    string command;
    vector<vector<shared_ptr<Interface>>> matrix;
    vector<shared_ptr<Interface>> flow_Vector;
    vector<string> name_flows_vector;
    vector<vector<int>>all_flows;
    vector<int> one_flow;
    bool loop_main_start = true;
    
    public:

    void show_a_flow_with_no_name(vector<int> flow) {
        int cnt = 0;
        cout<<"\n\t";
        for (const auto& element : flow) {
            cnt ++;
            cout<< "Step "<< cnt << ". "<<name_element_from_flow(element)<<"\n\t";
        }
        cout<<"\n\n";
    }

    // accesez un singrur flow si creez componentele + le accesez pe fiecare
    void acces_a_flow(vector<int>& myVector) {
        space_between();
        flow_Vector.clear();
        for (const auto& element : myVector) {
            show_a_flow_with_no_name(myVector);
            switch (element)
            {
            case 1:
                {
                    shared_ptr<Interface> new_title = make_shared<Title>();
                    new_title->execution();
                    flow_Vector.push_back(move(new_title));
                    break;
                }
            case 2:
            {
                break;
            }
            case 3:
            {
                shared_ptr<Interface> new_text_input = make_shared<Text_input>();
                new_text_input->execution();
                flow_Vector.push_back(move(new_text_input));
                break;
            }
            case 4:
            {
                shared_ptr<Interface> new_number_input = make_shared<Number_input>();
                new_number_input->execution();
                flow_Vector.push_back(move(new_number_input));
                break;
            }
            case 5:
            {
                shared_ptr<Interface> new_calculus = make_shared<Calculus>();
                new_calculus->get_the_flow(flow_Vector);
                new_calculus->execution();
                flow_Vector.push_back(move(new_calculus));
                break;
            }
            case 6:
            {
                shared_ptr<Interface> new_display = make_shared<Display>();
                new_display->get_the_flow(flow_Vector);
                new_display->execution();
                flow_Vector.push_back(move(new_display));
                break;
            }
            case 7:
            {
                shared_ptr<Interface> new_text_file_input = make_shared<Text_file_input>();
                new_text_file_input->execution();
                flow_Vector.push_back(move(new_text_file_input));
                break;
            }
            case 8:
            {
                shared_ptr<Interface> new_CSV_file_input = make_shared<CSV_file_input>();
                new_CSV_file_input->execution();
                flow_Vector.push_back(move(new_CSV_file_input));
                break;
            }
            case 9:
            {
                shared_ptr<Interface> new_output = make_shared<Output>();
                new_output->get_the_flow(flow_Vector);
                new_output->execution();
                flow_Vector.push_back(move(new_output));
                break;
            }
            default:
                break;
            }
        }
    }

// delete a specific flow
    void delete_a_flow(int x) {
        if (x <= all_flows.size() && x > -1) {
            all_flows.erase(all_flows.begin() + x);
            name_flows_vector.erase(name_flows_vector.begin() + x);
        } else{
            error_wrong_command();
            cout<<"Cannot delete that flow!!\n\n";
        }
    }

// aici accesez lista completa de de flow uri si de nume flow uri, si il aleg pe cel dorit.
    void menu_existing_flows() {
        space_between();
        bool wrong_ansnwer = false;
        while(true) {
            int cnt_flow = 0, cnt_pozition;
            for (const auto& flow : all_flows) {
                cnt_flow ++;
                cnt_pozition = 0;
                // afisez numele flow ului
                cout<<cnt_flow << ". "<< name_flows_vector[cnt_flow - 1]<< "\n\t";
                // afisez flow ul 
                show_a_flow_with_no_name(flow);
                cout<<endl<<endl;
            }

            // afisez ceva daca a apasat comanda gresita
            if (wrong_ansnwer == true) {
                cout<< "\nPlease press a value of an index of the desired flow, \"e\" if you want to exit or delete:INDEX!!\n";
            }
            // Se introduce optiunea
            cout<<"Choose an option (only the index necessary, \"e\" to esc or write \"delete:INDEX\" to delete a specific flow):";
            fflush(stdin);
            cin>>command;


            // verificare daca e numar si daca exista optiunea aceea
            if (all_of(command.begin(), command.end(), ::isdigit)) {
                int option = stoi(command);
                if(option <= cnt_flow) {
                    acces_a_flow(all_flows[option - 1]);
                } else {
                    cout<<"\n\nOut of range!!\n\n";
                }
            } else if (command == "e"){
                break;
            } else if(command.length() >7){
                string substring = command.substr(0, 7);
                string index_delete = command.substr(7);
                int index_d = 10000;    
                try
                {
                    index_d = stoi(index_delete);
                }catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid argument: " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Out of range: " << e.what() << std::endl;
                }
                    if(substring == "delete:" && index_d <=cnt_flow) {
                        wrong_ansnwer = false;
                        delete_a_flow(index_d - 1);

                    } else {
                        wrong_ansnwer = true;
                        error_wrong_command();    
                    }
            } else {
                wrong_ansnwer = true;
                error_wrong_command();
            }
            
        }
    }

    // create the new - comanda n de pe prima pagina
    void new_flow() {
        string name_flow;
        int cnt = 0;

        while(true) {
            space_between();
            cnt ++;
            cout<<"\tSelect options (press e to esc); the options you selected ase saved automatically:\n";
            cout<<"1.TITLE step: title (string), subtitle (string)\n";
            cout<<"2.TEXT step: title (string), copy (string)\n";
            cout<<"3.TEXT INPUT step: description (string), text input (string)\n";
            cout<<"4.NUMBER INPUT step: description (string), number input (float)\n";
            cout<<"5.CALCULUS step: steps (integer), operation (string)\n";
            cout<<"6.DISPLAY steps: step (integer)\n";
            // text is csv aici voi numi calea si numele file ului si eu voi crea o legatura cu el (pentru DISPLAY).
            cout<<"7.TEXT FILE input step: description, file_name \n";
            cout<<"8.CSV FILE input step: description, file_name\n";
            // aici creez un txt file
            cout<<"9.OUTPUT step: step (integer), name of file (string), title (text), description (text)\n";
            
            cout<<"\nThe " << cnt << " option: ";

            fflush(stdin);
            cin>> command;
            
            if( command == "e" && !one_flow.empty()) {
                all_flows.push_back(move(one_flow));
                one_flow.clear();

                cout<<"Give a name to this flow: ";
                fflush(stdin);
                getline(cin, name_flow);
                name_flow = trim(name_flow);
                cout<<name_flow;
                name_flows_vector.push_back(name_flow);
                break;
            } else if (command == "e") {
                break;
            }
            if(all_of(command.begin(), command.end(), ::isdigit) && command.length() == 1) {
                cout <<"You have added a: ";
                switch(command[0]) {
                    case '1':
                        {
                        one_flow.push_back(1);
                        cout << "Title" << "\n";
                        break;
                        }
                    case '2':
                        {
                        one_flow.push_back(2);
                        cout<<"Text\n";
                        break;
                        }
                    case '3':
                        {
                            one_flow.push_back(3);
                            cout<<"Text input\n";
                            break;
                        }
                    case '4':
                        {
                            one_flow.push_back(4);
                            cout<<"Number input\n";
                            break;
                        }
                    case '5':
                        {
                            one_flow.push_back(5);
                            cout<<"Calculus\n";
                            break;
                        }
                    case '6':
                        {
                            one_flow.push_back(6);
                            cout<<"Display\n";
                            break;
                        }
                    case '7':
                        {
                            one_flow.push_back(7);
                            cout<<"Text file\n";
                            break;
                        }
                    case '8':
                        {
                            one_flow.push_back(8);
                            cout<<"CSV file\n";
                            break;
                        }
                    case '9':
                        {
                            one_flow.push_back(9);
                            cout<<"Output\n";
                            break;
                        }
                    default:
                        {
                            cnt --;
                            cout<<"Aceasta nu este o optiune.\n";
                            break;
                        }
                }
            } else {
                cnt --;
                error_wrong_command();
                cout<<"The digit only please:)";
            }
            press_something();
        }
    }

    // Primul meniu care va aparea, acesta iti va da optiunile de creare nou flow, iesire si vizualizare flow uri curente.
    void menu_start() {
        while(loop_main_start) {
            space_between();
            cout<<"1.Create new flow (press n) \n";
            cout<<"2.Exit (press e)\n";
            if(!all_flows.empty()) {
                cout<<"3.Check available flows (press f)\n";
            }

            cout<<"Command:";
            fflush(stdin);
            cin>>command;
            if (ischaracter(command)) {
                switch(command[0]) {
                        case 'e':   
                            loop_main_start = false;
                            break;
                        case 'n':
                            new_flow();
                            break;
                        case 'f':
                            if (!all_flows.empty()) {
                                menu_existing_flows();
                            }
                            break;
                        default:
                            error_wrong_command();
                            cout <<"Comanda gresita, incearca din nou!!";
                            break;
                }
            }
        }
    }

};


int main() {
    Menu menu;
    menu.menu_start();
    return 0;
}