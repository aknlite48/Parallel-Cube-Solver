#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>
#include <random>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>


using namespace std;

//vector<int> SOLVED = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27};
vector<uint8_t> SOLVED = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

enum AV_MOVE {u,ui,d,di,r,ri,l,li,f,fi,b,bi};

string AV_MOVE_CONV[12] = {"U","U'","D","D'","R","R'","L","L'","F","F'","B","B'"};

vector<uint8_t> MOVE_LIST = {u,ui,d,di,r,ri,l,li,f,fi,b,bi};


/*
unordered_map<int,vector<int> > MOVES = {
	{u,{u,d,di,r,ri,l,li,f,fi,b,bi}},
	{ui,{ui,d,di,r,ri,l,li,f,fi,b,bi}},
	{d,{u,ui,d,r,ri,l,li,f,fi,b,bi}},
	{di,{u,ui,di,r,ri,l,li,f,fi,b,bi}},
	{r,{u,ui,d,di,r,l,li,f,fi,b,bi}},
	{ri,{u,ui,d,di,ri,l,li,f,fi,b,bi}},
	{l,{u,ui,d,di,r,ri,l,f,fi,b,bi}},
	{li,{u,ui,d,di,r,ri,li,f,fi,b,bi}},
	{f,{u,ui,d,di,r,ri,l,li,f,b,bi}},
	{fi,{u,ui,d,di,r,ri,l,li,fi,b,bi}},
	{b,{u,ui,d,di,r,ri,l,li,f,fi,b}},
	{bi,{u,ui,d,di,r,ri,l,li,f,fi,bi}}
};
*/

vector< vector<uint8_t> > MOVES = {
	{u,d,di,r,ri,l,li,f,fi,b,bi},
	{ui,d,di,r,ri,l,li,f,fi,b,bi},
	{u,ui,d,r,ri,l,li,f,fi,b,bi},
	{u,ui,di,r,ri,l,li,f,fi,b,bi},
	{u,ui,d,di,r,l,li,f,fi,b,bi},
	{u,ui,d,di,ri,l,li,f,fi,b,bi},
	{u,ui,d,di,r,ri,l,f,fi,b,bi},
	{u,ui,d,di,r,ri,li,f,fi,b,bi},
	{u,ui,d,di,r,ri,l,li,f,b,bi},
	{u,ui,d,di,r,ri,l,li,fi,b,bi},
	{u,ui,d,di,r,ri,l,li,f,fi,b},
	{u,ui,d,di,r,ri,l,li,f,fi,bi}
};


void MOVE(vector<uint8_t>& c,uint8_t &m) {
	switch (m) {
	case u:
		swap(c[0],c[5]);
		swap(c[5],c[7]);
		swap(c[7],c[2]);
		swap(c[1],c[3]);
		swap(c[3],c[6]);
		swap(c[6],c[4]);
		break;
	case ui:
		swap(c[0],c[2]);
		swap(c[2],c[7]);
		swap(c[7],c[5]);
		swap(c[1],c[4]);
		swap(c[4],c[6]);
		swap(c[6],c[3]);
		break;
	case d:
		swap(c[12],c[14]);
		swap(c[14],c[19]);
		swap(c[19],c[17]);
		swap(c[13],c[16]);
		swap(c[16],c[18]);
		swap(c[18],c[15]);
		break;
	case di:
		swap(c[12],c[17]);
		swap(c[17],c[19]);
		swap(c[19],c[14]);
		swap(c[15],c[18]);
		swap(c[18],c[16]);
		swap(c[16],c[13]);
		break;
	case r:
		swap(c[7],c[19]);
		swap(c[19],c[14]);
		swap(c[14],c[2]);
		swap(c[4],c[11]);
		swap(c[11],c[16]);
		swap(c[16],c[9]);
		break;
	case ri:
		swap(c[7],c[2]);
		swap(c[2],c[14]);
		swap(c[19],c[14]);
		swap(c[4],c[9]);
		swap(c[16],c[9]);
		swap(c[11],c[16]);
		break;
	case l:
		swap(c[0],c[12]);
		swap(c[12],c[17]);
		swap(c[17],c[5]);
		swap(c[3],c[8]);
		swap(c[8],c[15]);
		swap(c[15],c[10]);
		break;
	case li:
		swap(c[0],c[5]);
		swap(c[17],c[5]);
		swap(c[12],c[17]);
		swap(c[3],c[10]);
		swap(c[15],c[10]);
		swap(c[8],c[15]);
		break;
	case f:
		swap(c[5],c[17]);
		swap(c[17],c[19]);
		swap(c[19],c[7]);
		swap(c[6],c[10]);
		swap(c[10],c[18]);
		swap(c[18],c[11]);
		break;
	case fi:
		swap(c[5],c[7]);
		swap(c[19],c[7]);
		swap(c[17],c[19]);
		swap(c[6],c[11]);
		swap(c[18],c[11]);
		swap(c[10],c[18]);
		break;
	case b:
		swap(c[0],c[2]);
		swap(c[2],c[14]);
		swap(c[14],c[12]);
		swap(c[1],c[9]);
		swap(c[9],c[13]);
		swap(c[13],c[8]);
		break;
	case bi:
		swap(c[0],c[12]);
		swap(c[14],c[12]);
		swap(c[2],c[14]);
		swap(c[1],c[8]);
		swap(c[13],c[8]);
		swap(c[9],c[13]);
		break;
	}
}

// vector<int> SHUFFLE(vector<int>& c,int n_moves) {
// 	vector<int> shuff;
// 	srand(time(0)); 
// 	for (int i=0;i<n_moves;i++) {
// 		int m = (rand()%12);
// 		MOVE(c,m);
// 		shuff.push_back(m);
// 	}
// 	return shuff;
// }

void MOVE_FROM_SEQ(vector<uint8_t>& c,vector<uint8_t>& seq) {
	for (uint8_t &i: seq) {
		MOVE(c,i);
	}
}

vector<uint8_t> SOLVE_E(vector<uint8_t>& c,bool use_hash) { //cuts down memory by 1/4th
	vector<uint8_t> sol;

	if (!use_hash) {
	vector<uint8_t> c_orig = c;
	vector<uint8_t> sol;
	if (c_orig==SOLVED) {
		cout << "already solved" << endl;
		return sol;
	}
	queue<vector<uint8_t>> Q;
	std::vector<uint8_t>::size_type depth = 0;

	for (uint8_t &i: MOVE_LIST) {
		vector<uint8_t> c1 = c_orig;
		MOVE(c1,i);
		Q.push(vector<uint8_t> {i});
	}
	uint8_t k=1;

	while(!Q.empty()) {
		vector<uint8_t> s_i = Q.front();
		Q.pop();

		//if (k%10000==0) {
		cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
		//}

		if (s_i.size()>depth) {
			depth=s_i.size();
		}
		vector<uint8_t> c_i = c_orig;
		for (uint8_t &i: s_i) {
			MOVE(c_i,i);
		}
		if (c_i==SOLVED) {
			sol = s_i;
			cout << " " << endl;
			//cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
			cout << "Solution found" << endl;
			break;
		}
		for (uint8_t &i: MOVES[s_i.back()]) {
			vector<uint8_t> s_ii = s_i;
			s_ii.push_back(i);
			Q.push(s_ii);
		}
		k++;

	}
	return sol;

	}
	else {
	vector<uint8_t> c_orig = c;
	vector<uint8_t> sol;
	if (c_orig==SOLVED) {
		cout << "already solved" << endl;
		return sol;
	}
	queue<vector<uint8_t>> Q;
	std::vector<uint8_t>::size_type depth = 0;

	set<vector<uint8_t> > visited;
	int visits=0;


	for (uint8_t &i: MOVE_LIST) {
		vector<uint8_t> c1 = c_orig;
		MOVE(c1,i);
		Q.push(vector<uint8_t> {i});
	}
	int k=1;

	while(!Q.empty()) {
		vector<uint8_t> s_i = Q.front();
		Q.pop();

		//if (k%10000==0) {
		cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
		//}

		if (s_i.size()>depth) {
			depth=s_i.size();
		}
		vector<uint8_t> c_i = c_orig;
		for (uint8_t &i: s_i) {
			MOVE(c_i,i);
		}
		if (visited.count(c_i)) {
			visits++;
			continue;
		}
		else {
			visited.insert(c_i);
		}


		if (c_i==SOLVED) {
			sol = s_i;
			cout << " " << endl;
			//cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
			cout << "Solution found " << "Revisits: " << visits << endl;
			break;
		}
		for (uint8_t &i: MOVES[s_i.back()]) {
			vector<uint8_t> s_ii = s_i;
			s_ii.push_back(i);
			Q.push(s_ii);
		}
		k++;

	}
	return sol;
	}

	//return sol;
}



vector<uint8_t> SOLVE_M(vector<uint8_t>& c,bool use_hash) { //memory intensive
struct CUBE_STATE {
	vector<uint8_t> s;
	vector<uint8_t> c;

};
	if (!use_hash) {
	vector<uint8_t> c_orig = c;
	vector<uint8_t> sol;
	if (c_orig==SOLVED) {
		cout << "already solved" << endl;
		return sol;
	}
	queue<CUBE_STATE> Q;
	std::vector<uint8_t>::size_type depth = 0;

	for (uint8_t &i: MOVE_LIST) {
		vector<uint8_t> c1 = c_orig;
		MOVE(c1,i);
		Q.push({vector<uint8_t> {i},c1});
	}
	int k=1;

	while(!Q.empty()) {
		vector<uint8_t> s_i = Q.front().s;
		vector<uint8_t> c_i = Q.front().c;
		Q.pop();

		//if (k%10000==0) {
		cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
		//}

		if (s_i.size()>depth) {
			depth=s_i.size();
		}

		if (c_i==SOLVED) {
			sol = s_i;
			cout << " " << endl;
			//cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
			cout << "Solution found" << endl;
			break;
		}
		for (uint8_t &i: MOVES[s_i.back()]) {
			vector<uint8_t> s_ii = s_i;
			s_ii.push_back(i);
			vector<uint8_t> c_ii = c_i;
			MOVE(c_ii,i);
			Q.push({s_ii,c_ii});
		}
		k++;

	}
	return sol;
	}
	else {
	vector<uint8_t> c_orig = c;
	vector<uint8_t> sol;
	set<vector<uint8_t> > visited;
	if (c_orig==SOLVED) {
		cout << "already solved" << endl;
		return sol;
	}
	queue<CUBE_STATE> Q;
	std::vector<uint8_t>::size_type depth = 0;

	for (uint8_t &i: MOVE_LIST) {
		vector<uint8_t> c1 = c_orig;
		MOVE(c1,i);
		Q.push({vector<uint8_t> {i},c1});
	}
	int k=1; int visits=0;

	while(!Q.empty()) {
		vector<uint8_t> s_i = Q.front().s;
		vector<uint8_t> c_i = Q.front().c;
		Q.pop();

		if (visited.count(c_i)) {
			visits++;
			continue;
		}
		else {
			visited.insert(c_i);
		}

		//if (k%10000==0) {
		cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
		//} 

		if (s_i.size()>depth) {
			depth=s_i.size();
		}

		if (c_i==SOLVED) {
			sol = s_i;
			cout << " " << endl;
			//cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
			cout << "Solution found " << "Revisits: " << visits << endl;
			break;
		}
		for (uint8_t &i: MOVES[s_i.back()]) {
			vector<uint8_t> s_ii = s_i;
			s_ii.push_back(i);
			vector<uint8_t> c_ii = c_i;
			MOVE(c_ii,i);
			Q.push({s_ii,c_ii});
		}
		k++;

	}
	return sol;

	}
}

std::vector<uint8_t> PARSE_SEQ(const std::string& input) {
    std::vector<uint8_t> move_indices;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        bool found = false;

        for (uint8_t i = 0; i < 12; ++i) {
            if (AV_MOVE_CONV[i] == token) {
                move_indices.push_back(i);
                found = true;
                break;
            }
        }

        if (!found) {
            throw std::invalid_argument("Invalid move in shuffle: " + token);
        }
    }

    return move_indices;
}

std::string SHOW_SEQ(std::vector<uint8_t>& input) {
	string sequence;
	for (uint8_t &i:input) {
		sequence+=AV_MOVE_CONV[i]+" ";
	}
	sequence.pop_back();
	return sequence;
}

int main (int argc, char* argv[]) {

    char solver_type = 'E';   		// Optional
    bool use_hash = false;    		// Optional
    int n_moves = -1;         		// REQUIRED, optional if shuffle seq provided
    std::string shuffle_seq_raw;    // Optional

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--solver") {
            if (i + 1 < argc) {
                std::string val = argv[++i];
                if (val == "M" || val == "E") {
                    solver_type = val[0];
                } else {
                    std::cerr << "Invalid solver type: " << val << ". Use 'M' or 'E'.\n";
                    return 1;
                }
            } else {
                std::cerr << "Missing value for --solver\n";
                return 1;
            }
        } else if (arg == "--use_hash") {
            use_hash = true;
        } else if (arg == "--n_moves") {
            if (i + 1 < argc) {
                std::string val = argv[++i];
                try {
                    n_moves = std::stoi(val);
                } catch (const std::invalid_argument&) {
                    std::cerr << "Invalid value for --n_moves: not a number\n";
                    return 1;
                } catch (const std::out_of_range&) {
                    std::cerr << "Value for --n_moves is out of range\n";
                    return 1;
                }
            } else {
                std::cerr << "Missing value for --n_moves\n";
                return 1;
            }
        } else if (arg == "--shuffle") {
            if (i + 1 < argc) {
                shuffle_seq_raw = argv[++i];
                while (i + 1 < argc && argv[i + 1][0] != '-') {
                    shuffle_seq_raw += " " + std::string(argv[++i]);
                }
            } else {
                std::cerr << "Missing value for --shuffle\n";
                return 1;
            }
        }
        else {
            std::cerr << "Unknown argument: " << arg << "\n";
            return 1;
        }
    }

    // Enforce conditional requirement:
    if (shuffle_seq_raw.empty() && n_moves == -1) {
        std::cerr << "Error: You must provide either --n_moves or --shuffle.\n";
        return 1;
    }

    //generate random sequence if shuffle not provided
    if (shuffle_seq_raw.size()<1) {
		srand(time(0)); 
		for (int i=0;i<n_moves;i++) {
			int m = (rand()%12);
			shuffle_seq_raw+=AV_MOVE_CONV[m]+' ';
		}
		shuffle_seq_raw.pop_back();
    }
    printf("\n \n");
    std::cout << "       Cube Solver - Configuration\n";
    std::cout << "--------------------------------------------\n";
	std::cout << std::left << std::setw(25) << "    Solver type:"       << solver_type << "\n";
	std::cout << std::left << std::setw(25) << "    Use hash:"          << (use_hash ? "true" : "false") << "\n";


    int move_count = std::count(shuffle_seq_raw.begin(), shuffle_seq_raw.end(), ' ') + 1;
    std::cout << std::left << std::setw(25) << "    Number of moves:"   << move_count << "\n";
    std::cout << std::left << std::setw(25) << "    Shuffle sequence:"  << shuffle_seq_raw << "\n";
	
	std::cout << "--------------------------------------------\n";

    //initial cube state
	vector<uint8_t> cube = SOLVED;

	//initial sequence of shuffle moves
	auto initial_seq = PARSE_SEQ(shuffle_seq_raw);

	//move cube from shuffle move list
	MOVE_FROM_SEQ(cube,initial_seq);

	printf("\n \n");
	printf("Solver Status:");

	//apply solver
	vector<uint8_t> final_seq = (solver_type=='E') ? SOLVE_E(cube,use_hash) : SOLVE_M(cube,use_hash);

	//print final seq
	printf("\n");
	printf("Solution sequence: ");
	cout << SHOW_SEQ(final_seq) << endl;
}