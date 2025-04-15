#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <random>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <cstring> //added for cims compatibility
#include <cstdint>
#include <array>
#include <omp.h>


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

vector< vector<uint8_t> > MOVES_DOUB = {
    {d,di,r,ri,l,li,f,fi,b,bi},
    {d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi},
    {u,ui,d,di,r,ri,l,li,f,fi}
};

static const vector<vector<vector<uint8_t>>> MOVES_LOOKUP = {
{
    {d,di,r,ri,l,li,f,fi,b,bi},
    {d,di,r,ri,l,li,f,fi,b,bi},
    {u,d,r,ri,l,li,f,fi,b,bi},
    {u,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {d,di,r,ri,l,li,f,fi,b,bi},
    {d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,r,ri,l,li,f,fi,b,bi},
    {ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,r,ri,l,li,f,fi,b,bi},
    {ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,di,r,ri,l,li,f,fi,b,bi},
    {ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,f,fi,b,bi},
    {u,ui,d,di,r,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,f,fi,b,bi},
    {u,ui,d,di,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,f,fi,b,bi},
    {u,ui,d,di,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,li,f,fi,b,bi},
    {u,ui,d,di,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b},
    {u,ui,d,di,r,ri,l,li,f,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,b,bi},
    {u,ui,d,di,r,ri,l,li,fi,b},
    {u,ui,d,di,r,ri,l,li,fi,bi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,b},
    {u,ui,d,di,r,ri,l,li,fi,b},
    {u,ui,d,di,r,ri,l,li,f,fi},
    {u,ui,d,di,r,ri,l,li,f,fi}
    },
    {
    {u,d,di,r,ri,l,li,f,fi,b,bi},
    {ui,d,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,r,ri,l,li,f,fi,b,bi},
    {u,ui,di,r,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,l,li,f,fi,b,bi},
    {u,ui,d,di,ri,l,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,f,fi,b,bi},
    {u,ui,d,di,r,ri,li,f,fi,b,bi},
    {u,ui,d,di,r,ri,l,li,f,bi},
    {u,ui,d,di,r,ri,l,li,fi,bi},
    {u,ui,d,di,r,ri,l,li,f,fi},
    {u,ui,d,di,r,ri,l,li,f,fi}
    }
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

struct CubeState {
    // Use an array for simplicity
    std::array<uint8_t, 48> state;
    
    //default constructor : solved cube
    CubeState() {
        state = {u,u,u,u,u,u,u,u,l,l,l,f,f,f,r,r,r,b,b,b,l,l,f,f,r,r,b,b,l,l,l,f,f,f,r,r,r,b,b,b,d,d,d,d,d,d,d,d};
    }

    CubeState(const vector<uint8_t>& v) {
        for (int i = 0; i < min(48, static_cast<int>(v.size())); i++) {
            state[i] = v[i];
        }
    }
    
    // Equality operator
    bool operator==(const CubeState& other) const {
        return std::memcmp(state.data(), other.state.data(), 48 * sizeof(uint8_t)) == 0;
    }
};

namespace std {
    template <>
    struct hash<CubeState> {
        size_t operator()(const CubeState& cube) const {
            // FNV-1a hash algorithm - very fast and good distribution
            size_t hash = 14695981039346656037ULL; // FNV offset basis
            const uint8_t* data = cube.state.data();
            
            // Process all 48 bytes
            for (size_t i = 0; i < 48; ++i) {
                hash ^= static_cast<size_t>(data[i]);
                hash *= 1099511628211ULL; // FNV prime
            }
            
            return hash;
        }
    };
}




struct VectorHash {
    size_t operator()(const vector<uint8_t>& v) const {
        size_t hash = 0;
        for (size_t i = 0; i < v.size(); ++i) {
            hash = hash * 31 + v[i];
        }
        return hash;
    }
};

struct CompactSequence {
    uint64_t packed_moves;
    uint8_t length;
    
    // Default constructor
    CompactSequence() : packed_moves(0), length(0) {}
    
    // Constructor from vector<uint8_t>
    CompactSequence(const vector<uint8_t>& moves) : packed_moves(0), length(0) {
        for (const uint8_t& move : moves) {
            if (length < 16) { // Ensure we don't exceed capacity
                addMove(move);
            }
        }
    }
    
    // Add a single move
    void addMove(uint8_t move) {
        if (length < 16) { // Check capacity
            packed_moves |= (static_cast<uint64_t>(move & 0xF) << (length * 4));
            length++;
        }
    }
    
    // Get a move at a specific index
    uint8_t getMove(uint8_t index) const {
        if (index < length) {
            return (packed_moves >> (index * 4)) & 0xF;
        }
        return 0; // Or some error value
    }
    
    // Convert back to vector<uint8_t>
    vector<uint8_t> toVector() const {
        vector<uint8_t> result(length);
        for (uint8_t i = 0; i < length; i++) {
            result[i] = getMove(i);
        }
        return result;
    }
    
    // Push back (like vector)
    void push_back(uint8_t move) {
        addMove(move);
    }
    
    // Access operator (like vector)
    uint8_t operator[](uint8_t index) const {
        return getMove(index);
    }
    
    // Size accessor (like vector)
    uint8_t size() const {
        return length;
    }
    
    // Check if empty
    bool empty() const {
        return length == 0;
    }
    
    // Back element (like vector)
    uint8_t back() const {
        if (length > 0) {
            return getMove(length - 1);
        }
        return 0; // Or some error value
    }
};

inline void cycleClockwise4(std::array<uint8_t, 48>& state, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4) {
    uint8_t temp = state[i1];
    state[i1] = state[i4];
    state[i4] = state[i3];
    state[i3] = state[i2];
    state[i2] = temp;
}

inline void cycleCounterClockwise4(std::array<uint8_t, 48>& state, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4) {
    uint8_t temp = state[i1];
    state[i1] = state[i2];
    state[i2] = state[i3];
    state[i3] = state[i4];
    state[i4] = temp;
}

inline void moveF(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 11, 13, 33, 31);
        cycleClockwise4(cube.state, 12, 23, 32, 22);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 5, 14, 42, 30);
        cycleClockwise4(cube.state, 6, 24, 41, 21);
        cycleClockwise4(cube.state, 7, 34, 40, 10);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 11, 13, 33, 31);
        cycleCounterClockwise4(cube.state, 12, 23, 32, 22);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 5, 14, 42, 30);
        cycleCounterClockwise4(cube.state, 6, 24, 41, 21);
        cycleCounterClockwise4(cube.state, 7, 34, 40, 10);
    }
}

inline void moveR(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 14, 16, 36, 34);
        cycleClockwise4(cube.state, 15, 25, 35, 24);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 7, 17, 47, 33);
        cycleClockwise4(cube.state, 4, 26, 44, 23);
        cycleClockwise4(cube.state, 2, 37, 42, 13);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 14, 16, 36, 34);
        cycleCounterClockwise4(cube.state, 15, 25, 35, 24);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 7, 17, 47, 33);
        cycleCounterClockwise4(cube.state, 4, 26, 44, 23);
        cycleCounterClockwise4(cube.state, 2, 37, 42, 13);
    }  
}

inline void moveL(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 8, 10, 30, 28);
        cycleClockwise4(cube.state, 9, 21, 29, 20);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 0, 11, 40, 39);
        cycleClockwise4(cube.state, 3, 22, 43, 27);
        cycleClockwise4(cube.state, 5, 31, 45, 19);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 8, 10, 30, 28);
        cycleCounterClockwise4(cube.state, 9, 21, 29, 20);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 0, 11, 40, 39);
        cycleCounterClockwise4(cube.state, 3, 22, 43, 27);
        cycleCounterClockwise4(cube.state, 5, 31, 45, 19);
    }  
}

inline void moveU(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 0, 2, 7, 5);
        cycleClockwise4(cube.state, 1, 4, 6, 3);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 17, 14, 11, 8);
        cycleClockwise4(cube.state, 18, 15, 12, 9);
        cycleClockwise4(cube.state, 19, 16, 13, 10);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 0, 2, 7, 5);
        cycleCounterClockwise4(cube.state, 1, 4, 6, 3);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 17, 14, 11, 8);
        cycleCounterClockwise4(cube.state, 18, 15, 12, 9);
        cycleCounterClockwise4(cube.state, 19, 16, 13, 10);
    }  
}

inline void moveD(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 40, 42, 47, 45);
        cycleClockwise4(cube.state, 41, 44, 46, 43);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 28, 31, 34, 37);
        cycleClockwise4(cube.state, 29, 32, 35, 38);
        cycleClockwise4(cube.state, 30, 33, 36, 39);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 40, 42, 47, 45);
        cycleCounterClockwise4(cube.state, 41, 44, 46, 43);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 28, 31, 34, 37);
        cycleCounterClockwise4(cube.state, 29, 32, 35, 38);
        cycleCounterClockwise4(cube.state, 30, 33, 36, 39);
    }  
}

inline void moveB(CubeState& cube, bool clockwise) {
    if (clockwise) {
        // Face stickers
        cycleClockwise4(cube.state, 17, 19, 39, 37);
        cycleClockwise4(cube.state, 18, 27, 38, 26);
        
        // Surrounding stickers
        cycleClockwise4(cube.state, 16, 0, 28, 47);
        cycleClockwise4(cube.state, 25, 1, 20, 46);
        cycleClockwise4(cube.state, 36, 2, 8, 45);
    } else {
        // Face stickers
        cycleCounterClockwise4(cube.state, 17, 19, 39, 37);
        cycleCounterClockwise4(cube.state, 18, 27, 38, 26);
        
        // Surrounding stickers
        cycleCounterClockwise4(cube.state, 16, 0, 28, 47);
        cycleCounterClockwise4(cube.state, 25, 1, 20, 46);
        cycleCounterClockwise4(cube.state, 36, 2, 8, 45);
    }  
}

void MOVE_CUBE(CubeState& cube,uint8_t m) {
    switch(m) {
        case u: moveU(cube,true); break;
        case ui: moveU(cube,false); break;
        case d: moveD(cube,true); break;
        case di: moveD(cube,false); break;
        case r: moveR(cube,true); break;
        case ri: moveR(cube,false); break;
        case l: moveL(cube,true); break;
        case li: moveL(cube,false); break;
        case f: moveF(cube,true); break;
        case fi: moveF(cube,false); break;
        case b: moveB(cube,true); break;
        case bi: moveB(cube,false); break;
    }
}

void MOVE_CUBE_SEQUENCE(CubeState& c, CompactSequence& s) {
    for (uint8_t i = 0; i < s.size(); i++) {
        //uint8_t temp;

        MOVE_CUBE(c,s[i]);
        

    }
}

void MOVE_FROM_SEQ(vector<uint8_t>& c,vector<uint8_t>& seq) {
    for (uint8_t &i: seq) {
        MOVE(c,i);
    }
}

vector<uint8_t> SOLVE_E(CubeState& c_orig,bool use_hash,uint8_t max_depth) { //cuts down memory by 1/4th
    vector<uint8_t> sol;

    if (!use_hash) {
    //CubeState c_orig(c);
    CubeState solved;
    //vector<uint8_t> sol;
    if (c_orig==solved) {
        cout << "already solved" << endl;
        return sol;
    }
    queue<CompactSequence> Q;

    //load single move states
    for (uint8_t &i: MOVE_LIST) {
        //vector<uint8_t> c1 = c_orig;
        //MOVE(c1,i);
        Q.push(CompactSequence({i}));
    }
    //load double move states
    for (auto &i: MOVE_LIST) {
        for (auto &j: MOVES[i]) {
            Q.push(CompactSequence({i,j}));
        }
    }
    int k=1;

    //solve single move sequence: pops out all single move sequences
    int iter=0;
    while(!Q.empty() && (iter<12)) {
        auto s_i = Q.front();
        Q.pop();
        uint8_t seq_size = s_i.size();

        if (k%10000==0) {
        cout << "\r" << "Current depth: " << (int)seq_size << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
        }


        CubeState c_i = c_orig;
        MOVE_CUBE_SEQUENCE(c_i,s_i);

        if (c_i==solved) {
            sol = s_i.toVector();
            cout << " " << endl;
            //cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
            cout << "Solution found" << endl;
            return sol;
            //break;
        }

        auto last_move = s_i.back();
        //const vector<uint8_t>& allowed_moves = ((seq_size>1) && (last_move==s_i[seq_size-2])) ? MOVES_DOUB[last_move] : MOVES[last_move] ;
        const vector<uint8_t>& allowed_moves = MOVES[last_move];
        for (auto &i: allowed_moves) {
            CompactSequence s_ii(s_i);
            s_ii.push_back(i);
            Q.push(s_ii);
        }
        k++;iter++;

    }

    while(!Q.empty()) {
        auto s_i = Q.front();
        Q.pop();
        uint8_t seq_size = s_i.size();

        if (k%10000==0) {
        cout << "\r" << "Current depth: " << (int)seq_size << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
        }


        CubeState c_i = c_orig;
        MOVE_CUBE_SEQUENCE(c_i,s_i);

        if (c_i==solved) {
            sol = s_i.toVector();
            cout << " " << endl;
            //cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
            cout << "Solution found" << endl;
            break;
        }
        if (seq_size<max_depth) {
            auto last_move = s_i.back();
            //const vector<uint8_t>& allowed_moves = ((seq_size>1) && (last_move==s_i[seq_size-2])) ? MOVES_DOUB[last_move] : MOVES[last_move] ;
            //const vector<uint8_t>& allowed_moves = (seq_size>1) ? MOVES_LOOKUP[s_i[seq_size-2]][last_move] : MOVES[last_move];
            const vector<uint8_t>& allowed_moves = MOVES_LOOKUP[s_i[seq_size-2]][last_move];
            for (auto &i: allowed_moves) {
                CompactSequence s_ii(s_i);
                s_ii.push_back(i);
                //Q.push(s_ii);
                Q.push(std::move(s_ii));
            }
        }   
        k++;

    }
    return sol;

    }
    else {
    //CubeState c_orig(c);
    CubeState solved;
    //vector<uint8_t> sol;
    if (c_orig==solved) {
        cout << "already solved" << endl;
        return sol;
    }
    queue<CompactSequence> Q;
    unordered_set<CubeState> visited;
    int visits=0;

    //load single move states
    for (uint8_t &i: MOVE_LIST) {
        //vector<uint8_t> c1 = c_orig;
        //MOVE(c1,i);
        Q.push(CompactSequence({i}));
    }
    //load double move states
    for (auto &i: MOVE_LIST) {
        for (auto &j: MOVES[i]) {
            Q.push(CompactSequence({i,j}));
        }
    }
    int k=1;

    //solve single move sequence: pops out all single move sequences
    int iter=0;
    while(!Q.empty() && (iter<12)) {
        auto s_i = Q.front();
        Q.pop();
        uint8_t seq_size = s_i.size();

        if (k%10000==0) {
        cout << "\r" << "Current depth: " << (int)seq_size << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
        }


        CubeState c_i = c_orig;
        MOVE_CUBE_SEQUENCE(c_i,s_i);

        if (c_i==solved) {
            sol = s_i.toVector();
            cout << " " << endl;
            //cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
            cout << "Solution found" << endl;
            return sol;
            //break;
        }

        auto last_move = s_i.back();
        //const vector<uint8_t>& allowed_moves = ((seq_size>1) && (last_move==s_i[seq_size-2])) ? MOVES_DOUB[last_move] : MOVES[last_move] ;
        const vector<uint8_t>& allowed_moves = MOVES[last_move];
        for (auto &i: allowed_moves) {
            CompactSequence s_ii(s_i);
            s_ii.push_back(i);
            Q.push(s_ii);
        }
        k++;iter++;

    }

    while(!Q.empty()) {
        auto s_i = Q.front();
        Q.pop();
        uint8_t seq_size = s_i.size();

        if (k%10000==0) {
        cout << "\r" << "Current depth: " << (int)seq_size << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
        }


        CubeState c_i = c_orig;
        MOVE_CUBE_SEQUENCE(c_i,s_i);
        if (visited.count(c_i)) {
            visits++;
            continue;
        }
        else {
            visited.insert(c_i);
        }

        if (c_i==solved) {
            sol = s_i.toVector();
            cout << " " << endl;
            //cout << "\r" << "Current depth: " << depth << " Nodes searched: " << k << " Nodes remaining: " << Q.size();
            cout << "Solution found " << "Revisits: " << visits << endl;
            break;
        }
        if (seq_size<max_depth) {
            auto last_move = s_i.back();
            //const vector<uint8_t>& allowed_moves = ((seq_size>1) && (last_move==s_i[seq_size-2])) ? MOVES_DOUB[last_move] : MOVES[last_move] ;
            //const vector<uint8_t>& allowed_moves = (seq_size>1) ? MOVES_LOOKUP[s_i[seq_size-2]][last_move] : MOVES[last_move];
            const vector<uint8_t>& allowed_moves = MOVES_LOOKUP[s_i[seq_size-2]][last_move];
            for (auto &i: allowed_moves) {
                CompactSequence s_ii(s_i);
                s_ii.push_back(i);
                //Q.push(s_ii);
                Q.push(std::move(s_ii));
            }
        }   
        k++;

    }
    return sol;
    }

    return sol;
}


vector<uint8_t> SOLVE_B(const CubeState& c_orig, int max_depth = 20) {
    vector<uint8_t> sol;
    CubeState solved;
    
    // Check if already solved
    if (c_orig == solved) {
        cout << "Already solved" << endl;
        return sol;
    }
    
    // Store visited states from forward search
    // Map from cube state to the move sequence that reaches it
    unordered_map<CubeState, CompactSequence> forward_visited;
    
    // Store visited states from backward search
    // Map from cube state to the move sequence that reaches it
    unordered_map<CubeState, CompactSequence> backward_visited;
    
    // Queue for forward search (from initial state)
    queue<pair<CubeState, CompactSequence>> forward_queue;
    
    // Queue for backward search (from solved state)
    queue<pair<CubeState, CompactSequence>> backward_queue;
    
    // Inverse move mapping - for the backward search
    // This maps each move to its inverse move
    unordered_map<uint8_t, uint8_t> inverse_move = {
        {AV_MOVE::u, AV_MOVE::ui}, {AV_MOVE::ui, AV_MOVE::u},
        {AV_MOVE::d, AV_MOVE::di}, {AV_MOVE::di, AV_MOVE::d},
        {AV_MOVE::r, AV_MOVE::ri}, {AV_MOVE::ri, AV_MOVE::r},
        {AV_MOVE::l, AV_MOVE::li}, {AV_MOVE::li, AV_MOVE::l},
        {AV_MOVE::f, AV_MOVE::fi}, {AV_MOVE::fi, AV_MOVE::f},
        {AV_MOVE::b, AV_MOVE::bi}, {AV_MOVE::bi, AV_MOVE::b}
    };
    
    // Initialize forward search with initial state
    forward_queue.push({c_orig, CompactSequence()});
    forward_visited[c_orig] = CompactSequence();
    
    // Initialize backward search with solved state
    backward_queue.push({solved, CompactSequence()});
    backward_visited[solved] = CompactSequence();
    
    int nodes_searched = 0;
    bool solution_found = false;
    CompactSequence forward_path, backward_path;
    
    // Main search loop
    while (!forward_queue.empty() && !backward_queue.empty() && !solution_found) {
        // Expand forward search by one level


        vector<pair<CubeState, CompactSequence>> forward_queue_local;
        while (!forward_queue.empty()) {
            forward_queue_local.push_back(forward_queue.front());
            forward_queue.pop();
        }
        int forward_level_size = forward_queue_local.size();
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < forward_level_size ; i++) {
            if (solution_found) continue;
            auto [current_state, move_sequence] = forward_queue_local[i];
            
            uint8_t seq_size = move_sequence.size();
            
            // Check depth limit
            if (seq_size >= max_depth / 2) {
                continue;
            }
            
            // Get last move(s) for pruning
            uint8_t last_move = seq_size > 0 ? move_sequence.back() : 255;
            uint8_t second_last_move = seq_size > 1 ? move_sequence[seq_size - 2] : 255;
            
            // Determine allowed moves
            const vector<uint8_t>& allowed_moves = (seq_size > 1) ? 
                MOVES_LOOKUP[second_last_move][last_move] : 
                (seq_size > 0 ? MOVES[last_move] : MOVE_LIST);
            
            // Try each allowed move
            for (auto move : allowed_moves) {
                CubeState next_state = current_state;
                MOVE_CUBE(next_state, move);
                CompactSequence next_sequence = move_sequence;
                next_sequence.push_back(move);
                // cout<<"hekkoi"<<endl;
                #pragma omp critical
                {
                    if (forward_visited.find(next_state) == forward_visited.end()) {
                        forward_visited[next_state] = next_sequence;
                        forward_queue.push({next_state, next_sequence});

                        if (backward_visited.find(next_state) != backward_visited.end()) {
                            #pragma omp critical (solution_found)
                            {
                                solution_found = true;
                                forward_path = next_sequence;
                                backward_path = backward_visited[next_state];
                            }
                        }
                    }
                }
            }
            
            #pragma omp atomic
            nodes_searched++;

            if (nodes_searched % 10000 == 0) {
                cout << "\r" << "Nodes searched: " << nodes_searched 
                     << " Forward queue: " << forward_queue.size() 
                     << " Backward queue: " << backward_queue.size();
            }
        }
        
        if (solution_found) break;
        
        // Expand backward search by one level
        vector<pair<CubeState, CompactSequence>> backward_queue_local;
        while (!backward_queue.empty()) {
            backward_queue_local.push_back(backward_queue.front());
            backward_queue.pop();
        }
        int backward_level_size = backward_queue_local.size();
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < backward_level_size ; i++) {
            if (solution_found) continue;
            auto [current_state, move_sequence] = backward_queue_local[i];
            uint8_t seq_size = move_sequence.size();
            
            // Check depth limit
            if (seq_size >= max_depth / 2) {
                continue;
            }
            
            // Get last move(s) for pruning
            uint8_t last_move = seq_size > 0 ? move_sequence.back() : 255;
            uint8_t second_last_move = seq_size > 1 ? move_sequence[seq_size - 2] : 255;
            
            // Determine allowed moves - we need inverse moves for backward search
            const vector<uint8_t>& prune_moves = (seq_size > 1) ? 
                MOVES_LOOKUP[second_last_move][last_move] : 
                (seq_size > 0 ? MOVES[last_move] : MOVE_LIST);
                
            // We need to apply inverse moves for the backward search
            vector<uint8_t> allowed_moves;
            for (auto move : prune_moves) {
                allowed_moves.push_back(inverse_move[move]);
            }
            
            // Try each allowed move
            for (auto move : allowed_moves) {
                CubeState next_state = current_state;
                MOVE_CUBE(next_state, move);
                
                // Skip if already visited in backward search
                if (backward_visited.find(next_state) != backward_visited.end()) {
                    continue;
                }
                
                // Create new move sequence
                CompactSequence next_sequence = move_sequence;
                next_sequence.push_back(move);
                
                #pragma omp critical
                {
                     // Store in visited states
                    backward_visited[next_state] = next_sequence;

                    if (forward_visited.find(next_state) != forward_visited.end()) {
                        // Found a meeting point - solution found!
                        #pragma omp critical (solution_found)
                        {
                            forward_path = forward_visited[next_state];
                            backward_path = next_sequence;
                            solution_found = true;
                        }
                    }
                    // Add to queue for next level
                    backward_queue.push({next_state, next_sequence});
                
                }
            }

            #pragma omp atomic
            nodes_searched++;
            if (nodes_searched % 10000 == 0) {
                cout << "\r" << "Nodes searched: " << nodes_searched 
                     << " Forward queue: " << forward_queue.size() 
                     << " Backward queue: " << backward_queue.size();
            }
        }
    }
    
    if (solution_found) {
        cout << endl << "Solution found!" << endl;
        
        // Construct the complete solution
        // Forward path + Reversed backward path (need to use inverse moves)
        sol = forward_path.toVector();
        int forward_length = forward_path.size();
        int backward_length = backward_path.size();
        
        // Add reversed backward path
        vector<uint8_t> backward_vec = backward_path.toVector();
        for (int i = backward_vec.size() - 1; i >= 0; i--) {
            sol.push_back(inverse_move[backward_vec[i]]);
        }
        
        cout << "Solution length: " << sol.size() << endl;
        cout << "Forward path length: " << forward_length << endl;
        cout << "Backward path length: " << backward_length << endl;
        cout << "Forward states explored: " << forward_visited.size() << endl;
        cout << "Backward states explored: " << backward_visited.size() << endl;
    } else {
        cout << endl << "No solution found within depth limit." << endl;
    }
    
    return sol;
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

    char solver_type = 'E';         // Optional
    bool use_hash = false;          // Optional
    int n_moves = -1;               // REQUIRED, optional if shuffle seq provided
    std::string shuffle_seq_raw;    // Optional
    uint8_t max_depth = 20;         // Gods Number

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--solver") {
            if (i + 1 < argc) {
                std::string val = argv[++i];
                if (val == "B" || val == "E") {
                    solver_type = val[0];
                } else {
                    std::cerr << "Invalid solver type: " << val << ". Use 'B' or 'E'.\n";
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
        } else if (arg == "--max_depth") {
            if (i + 1 < argc) {
                std::string val = argv[++i];
                try {
                    int value = stoi(val);
                    if (value < 0 || value > 255) {
                        std::cerr << "Value out of range for uint8_t\n";
                        return 1;
                    }
                    max_depth = static_cast<uint8_t>(value);
                    } catch (const std::invalid_argument&) {
                    std::cerr << "Invalid value for --n_moves: not a number\n";
                    return 1;
                    } catch (const std::out_of_range&) {
                        std::cerr << "Value for --n_moves is out of range\n";
                        return 1;
                    }
                    
                }
            else {
                std::cerr << "Missing value for --max_depth\n";
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
    std::cout << std::left << std::setw(25) << "    Max depth:"  << (int)max_depth << "\n";
    std::cout << "--------------------------------------------\n";

    //initial cube state
    //vector<uint8_t> cube = SOLVED;
    CubeState cube;


    //initial sequence of shuffle moves
    auto initial_seq = PARSE_SEQ(shuffle_seq_raw);

    //move cube from shuffle move list
    CompactSequence initial_seq_compact(initial_seq);
    MOVE_CUBE_SEQUENCE(cube,initial_seq_compact);

    printf("\n \n");
    printf("Solver Status:");

    //apply solver
    vector<uint8_t> final_seq = (solver_type=='E') ? SOLVE_E(cube,use_hash,max_depth) : SOLVE_B(cube,max_depth);

    //vector<uint8_t> final_seq = SOLVE_E(cube,use_hash,max_depth);
    //vector<uint8_t> final_seq = solveCubeBidirectional(cube);

    //print final seq
    printf("\n");
    printf("Solution sequence: ");
    cout << SHOW_SEQ(final_seq) << endl;
}