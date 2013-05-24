#!/usr/bin/python
import MySQLdb
import utils 


class Mysql:
    class __impl:
        def __init__(self,addr):
            self.addr = addr 
            self.db_conn = utils.sql_db_connection(self.addr)
            self.db_cursor = self.db_conn.cursor()
        def execute(self,sql):
            try:
                res = self.db_cursor.execute(sql)
            except (MySQLdb.OperationalError):
                self.db_conn = utils.sql_db_connection(self.addr)
                self.db_cursor = self.db_conn.cursor()
                res = self.db_cursor.execute(sql)
            self.db_conn.commit()
            return res
        def fetchone(self):
            return self.db_cursor.fetchone()
        def fetchall(self):
            return self.db_cursor.fetchall()
        def lastrowid(self):
            return self.db_cursor.lastrowid
        def literal(self,s):
            return self.db_conn.literal(s)
       
    __instance = None
    def __init__(self,addr):
        if Mysql.__instance is None:
            Mysql.__instance = Mysql.__impl(addr)
        self.__dict__['_Singleton__instance'] = Mysql.__instance
    def __getattr__(self, attr):
        return getattr(self.__instance, attr)
    def __setattr__(self, attr, value):
        return setattr(self.__instance, attr, value)
 
    
if __name__=="__main__":
    m1 = Mysql("mysql:uc05,root,z64577580,zhaopin")
    m2 = Mysql("mysql:uc05,root,z64577580,zhaopin")
