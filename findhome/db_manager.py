import mysql.connector
from mysql.connector import errorcode


class DBLogger:
    def __init__(self, log_file_loc):        
        self.log_file_loc = log_file_loc
        self.log_file = open(self.log_file_log, 'a')    
    def log(message):
        self.log_file.write(message)
    def close():
        self.log_file.close()


class DBManager:
    def __init__(self, db_config_file):
        self.config_keys = ['user', 'password', 'host', 'database']
        self.db_config_file = db_config_file
        self.logger = DBLogger('db.log')
        self.db_conn = connect()

    def verify():
        pass

    def connect(self):
        db_config = load_config()
        db_conn = None
        try:
            db_conn = mysql.connector.connect(**db_config)
        except mysql.connector.Error as err:
            if err.errno == errorcode.ER_ACCESS_DENIED_ERROR:
                self.logger.log("Something is wrong with your user name or password")
            elif  err.errno == errorcode.ER_BAD_DB_ERROR:
                self.logger.log("Database does not exist")
            else:
                self.logger.log(err)
        return db_conn

    def load_config(self):    
        config_data = {}
        with open(self.db_config_file, 'r') as f:
            for line in f:
                key,value = line.split(sep='=')
                if key not in self.config_keys:
                    (self.logger.log('Invalid DB Configuration File : Key ' +
                    key + ' is invalid'))
                else:
                    config_data[key] = value
        return config_data
    
    def close():
        self.close()

