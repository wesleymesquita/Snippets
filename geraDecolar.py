import datetime
import os

"""
    This script has some facilities to generate multiple destination queries
    to www.decolar.com, a very used air tickets sale integrator in latin america

    @author Wesley Mesquita
"""

def decomposeFlights(flights):
    from_list = []
    to_list = []
    date_list = []
    for flight in flights:
        from_str, to_str, date_str = flight
        from_list.append(from_str)
        to_list.append(to_str)
        if '/' in date_str:
            d,m,y = date_str.split('/')
            date_list.append(str(y + "-"  + m + "-" + d))
        elif  '-' in date_str:
            d,m,y = date_str.split('/')
            date_list.append(str(y + "-"  + m + "-" + d))
        else:
            print "Error in decompose Flights! No date separator known"
            
    return from_list, to_list, date_list

def createDecolarUrlFromFlights(flights):
    from_list, to_list, date_list = decomposeFlights(flights)   
    base_decolar_url = "http://www.decolar.com/shop/flights/results/multipledestinations/"
    url = base_decolar_url +  str( ",".join(from_list) + "/" + ",".join(to_list) + "/" + ",".join(date_list) ) + "/2/0/0"
    return url

def createDecolarUrlFromDestData(from_list, to_list, date_list ):
    base_decolar_url = "http://www.decolar.com/shop/flights/results/multipledestinations/"
    url = base_decolar_url +  str( ",".join(from_list) + "/" + ",".join(to_list) + "/" + ",".join(date_list) ) + "/2/0/0"
    return url

def shiftFlightsKeepIntervals(flights, days):
    from_list, to_list, date_list = decomposeFlights(flights) 
    datetime_list = []
    for date in date_list:
        y,m,d = date.split('-')
        datetime_list.append(datetime.date(int(y), int(m), int(d)))
   
    for  i in range(0, len(datetime_list)):
        datetime_list[i] =  datetime_list[i] + datetime.timedelta(days=days)    

    date_list = [dt.strftime("%Y-%m-%d") for dt in datetime_list]
    
    url = createDecolarUrlFromDestData(from_list, to_list, date_list)
    return url
  
def invertRoute(flights):  
    from_list = []
    to_list = []
    date_list = []
    for flight in flights:
        from_str, to_str, date_str = flight
        from_list.append(from_str)
        to_list.append(to_str)
        date_list.append(date_str)
       
    full_rote  = []
    for i in range(0,len(from_list)):
        full_rote.append(from_list[i])
        full_rote.append(to_list[i])
       
    rev_full_rote = []
    [rev_full_rote.append(elem) for elem in reversed(full_rote)]
    
    from_list = []
    to_list = []
    
    for i in range(0, len(rev_full_rote)):
        if i%2 == 0:
            from_list.append(rev_full_rote[i]) 
        else:
            to_list.append(rev_full_rote[i])
    
    inverted_route = []
    for i in range(0, len(from_list)):
        from_, to_, date_ = from_list[i], to_list[i], date_list[i]
        inverted_route.append([from_, to_, date_])
    
    return inverted_route        
     
def backupURLs(destFile, urls):
    f = open(destFile, "")
      
     
     
def test():
    destinations = []
    destinations.append(['SAO', 'MUC', '05/05/2014'])
    destinations.append(['PAR', 'LIS', '14/05/2014'])
    destinations.append(['LIS', 'SAO', '21/05/2014'])
      
    urls = [] 
    
    for i in range(-3,3):
        url = shiftFlightsKeepIntervals(destinations, i)
        urls.append(url)
    
    inverted_dest = invertRoute(destinations);
    for i in range(-3,3):
        url = shiftFlightsKeepIntervals(inverted_dest, i)
        urls.append(url)
    
    for url in urls:
        print url
        os.system("start chrome " + url)

def test2():
    br_airports = [ 'BEL', 'CNF', 'BSB',  'CGR','CGB', 'CWB','FLN','FOR','GYN','JCB','JPA','MCP','MCZ','MAO','QGF','NAT','POA','PVH','REC','RBR','RIO','GIG','SSA','BLZ','SAO','CGH','GRU','VCP','THE','UDI','VIX']
    d = datetime.date.today() + datetime.timedelta(days=2)
    
    destinations = []

    for i in range(1,4):
        date_str = str(d.day) + '/' + str(d.month) + '/' + str(d.year)
        destinations.append( [br_airports[i], br_airports[i+1], date_str])
        d = d + datetime.timedelta(days=1)
    
    url = createDecolarUrlFromFlights(destinations)
    os.system("start chrome " + url)
test2()
    