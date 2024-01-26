from apps import db

#This file contains important models for the web application
class Book(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(64))

# _Under Construction_
#  class UserProfile(db.Model):
#      name = db.Column(db.String(64))
#      email = db.Column(db.String(64))
#      phoneNo = db.Column(db.String(64))
#      desc = db.Column(db.String(128))
    