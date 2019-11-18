//
//  Island.hpp
//  CS 211 Program 6 Archipelago
//
//  Created by Viktor Kirillov on 11/17/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Island_hpp
#define Island_hpp

#include "MyList.hpp"

class Island {
private:
    MyList m_connections;
    unsigned m_id;
    bool m_isVisited;
    
public:
    Island(unsigned id);
    
    void connect(Island *island);
    void disconnect(Island *island);
    
    bool isConnected(Island *island);
    
    unsigned getId() { return m_id; }
    MyList& getConnections() { return m_connections; }
    
    void setVisited(bool v) { m_isVisited = v; }
    bool getVisited() { return m_isVisited; }
};

#endif /* Island_hpp */
