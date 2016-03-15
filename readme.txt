I chose to use cities around Los Angeles, since that is where LAVC is.  I made them all have bidirectional edges, as that makes sense.  Not all cities connect, though.  Tucson is the southeast corner and only connects to Phoenix and San Diego.  San Francisco connects to only Los Angeles and Las Vegas.  Los Angeles connects to all cities except Tucson.

Direct Connections are written in my load.txt with the departure city, followed then any number of (a comma, destination city, comma, and distance) and then by a new line.  These are:
LA->San Diego LA->Phoenix LA->Las Vegas LA->San Francisco (4)
San Diego->Tucson San Diego->Phoenix San Diego->Los Angeles (3)
Tucson->Phoenix Tucson->San Diego (2)
Phoenix->Tucson Phoenix->Las Vegas Phoenix->LA Phoenix->San Diego (4)
Las Vegas->Phoenix Las Vegas->San Francisco Las Vegas->LA (3)
San Francisco->LA San Francisco->Las Vegas (2)
Total = 4 + 3 + 2 + 4 + 3 + 2 = 18 Direct Connections

Through connections will be large as all the cities have bidirectional edges.  I got from my running my program:
LA to San Diego (6)
LA to Tucson (8)
LA to Phoenix (4)
LA to Las Vegas (4)
LA to San Francisco (4)
LA Total = 6 + 8 + 4 + 4 + 4 = 26
San Diego to LA (6)
San Diego to Tucson (4)
San Diego to Phoenix (4)
San Diego to Las Vegas (9)
San Diego to San Francisco (11)
San Diego Total = 6 + 4 + 4 + 9 + 11 = 29
Tucson to LA (8)
Tucson to San Diego (4)
Tucson to Phoenix (4)
Tucson to Las Vegas (4)
Tucson to San Francisco (13)
Tucson Total = 8 + 4 + 4 + 4 + 13 = 33
Phoenix to LA (4)
Phoenix to San Diego (4)
Phoenix to Tucson (4)
Phoenix to Las Vegas (6)
Phoenix to San Francisco (8)
Phoenix Total = 4 + 4 + 4 + 6 + 8 = 26
Las Vegas to LA (4)
Las Vegas to San Diego (9)
Las Vegas to Tucson (11)
Las Vegas to Phoenix (6)
Las Vegas to San Francisco (4)
Las Vegas Total = 4 + 9 + 11 + 6 + 4 = 34
San Francisco to LA (4)
San Francisco to San Diego (11)
San Francisco to Tucson (13)
San Francisco to Phoenix (8)
San Francisco to Las Vegas (4)
San Francisco Total = 4 + 11 + 13 + 8 + 4 = 40
Total = 26 + 29 + 33 + 26 + 34 + 40 = 188 Through Connections