//
//  Island.cpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Island.hpp"

Island::Island(unsigned id): m_id(id), m_isVisited(false) {
    
}

void Island::connect(Island *island) {
    m_connections.push(island);
}

void Island::disconnect(Island *island) {
    m_connections.searchAndDelete(island);
}

bool Island::isConnected(Island *island) {
    return m_connections.search(island);
}
