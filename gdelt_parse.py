import sys
import pymongo
import datetime

from pymongo import MongoClient

''' GDELT2MONGODB - Extract GDELT CSV data into MongoDB
@author Wesley Mesquita
@email wesleymesquita@gmail.com 
'''

def getMongoClient(mongoserverURL, mongoserverPort):
	'''Get a MongoClient object based on connection string
	Ex: 
	'''	

	try:
		client = MongoClient(mongoserverURL, mongoserverPort)
		return client
	except Exception, e:
		print "Error in getCollection", e
		
def getMongoDB(mongoClient, database):
	'''
	Get a database given on a MongoClient object
	and the database name
	'''
	try:
		return mongoClient[database]
	except Exception, e: 
		print "[Error] in getMongoDB :", e

def getMongoCollection(mongoDB, collectionName):
	'''
	Get a collection given the database object and the collectionName
	'''
	try:
		return mongoDB[collectionName]
	except Exception, e:
		print "[Error]  getCollection :", e

def closeMongoDBConnection(mongoClient):
	try:
		mongoClient.close()
	except Exception, e:
		print "[Error] closeMongoDBConnection", e
		
GDELT_LABELS = ['GLOBALEVENTID', 'SQLDATE', 'MonthYear', 'Year', 'FractionDate', 'Actor1Code', 'Actor1Name', 'Actor1CountryCode', 'Actor1KnownGroupCode', 'Actor1EthnicCode', 'Actor1Religion1Code', 'Actor1Religion2Code', 'Actor1Type1Code', 'Actor1Type2Code', 'Actor1Type3Code', 'Actor2Code', 'Actor2Name', 'Actor2CountryCode', 'Actor2KnownGroupCode', 'Actor2EthnicCode', 'Actor2Religion1Code', 'Actor2Religion2Code', 'Actor2Type1Code', 'Actor2Type2Code', 'Actor2Type3Code', 'IsRootEvent', 'EventCode', 'EventBaseCode', 'EventRootCode', 'QuadClass', 'GoldsteinScale', 'NumMentions', 'NumSources', 'NumArticles', 'AvgTone', 'Actor1Geo_Type', 'Actor1Geo_FullName', 'Actor1Geo_CountryCode', 'Actor1Geo_ADM1Code', 'Actor1Geo_Lat', 'Actor1Geo_Long', 'Actor1Geo_FeatureID', 'Actor2Geo_Type', 'Actor2Geo_FullName', 'Actor2Geo_CountryCode', 'Actor2Geo_ADM1Code', 'Actor2Geo_Lat', 'Actor2Geo_Long', 'Actor2Geo_FeatureID', 'ActionGeo_Type', 'ActionGeo_FullName', 'ActionGeo_CountryCode', 'ActionGeo_ADM1Code', 'ActionGeo_Lat', 'ActionGeo_Long', 'ActionGeo_FeatureID', 'DATEADDED', 'SOURCEURL']
		
def isNumber(str):
	try:
		float(str)
		return True
	except:
		return False

def createGDELTMongoDocument(entries):
	try:
		doc = {}
		# First pass create a raw document
		for label, entry in zip(GDELT_LABELS, entries):
			doc[label] = None if entry == "" else entry
			
		# Second pass do some steps to get advantages of BSON:

		# 1) Coalesce ActionGeo_Lat and ActionGeo_Long into a 
		# single localization entry
		latitude = doc["ActionGeo_Lat"]
		longitude = doc["ActionGeo_Long"] 
		if latitude and longitude:
			del(doc["ActionGeo_Lat"])
			del(doc["ActionGeo_Long"])
			doc["ActionGeo_LatLong"] = "[" + latitude + "," + longitude + "]"
			
		# 2) load a datetime object for 'DATEADDED' field  into the map
		date_str = doc["DATEADDED"]
		year, month, day = date_str[0:4], date_str[4:6], date_str[6:8] 
		doc["DATEADDED"] = datetime.datetime( int(year), int(day), int(month), 12, 0)

		# 3) Coalesce actor geolocalization
		latitude = doc["Actor2Geo_Lat"]
		longitude = doc["Actor2Geo_Long"] 
		if latitude and longitude:
			del(doc["Actor2Geo_Lat"])
			del(doc["Actor2Geo_Long"])
			doc["Actor2Geo_LatLong"] = "[" + latitude + "," + longitude + "]"
			
		return doc	
	except Exception, e:
		print "[Error] createGDELTMongoDocument: ", e
	 

def exportGDELTToMongo(file, mongoServerURL, mongoPort, mongoDB, mongoCollection):
	client = getMongoClient(mongoServerURL, mongoPort)
	db = getMongoDB(client, mongoDB)
	collection = getMongoCollection(db, mongoCollection)

	try:
		gdelt_file = open(sys.argv[1], "r")	
		lines = gdelt_file.readlines()

		for line in lines:
			entries = line.split('\t')
			doc = createGDELTMongoDocument(entries)
			collection.insert(doc)
		closeMongoDBConnection(client)
		gdelt_file.close()
	except Exception, e:
		print "[Error]  exportGDELTToMongo", e

	
def main():
	exportGDELTToMongo(sys.argv[1], "localhost", 27017, "gedelt", "docs")

main()
