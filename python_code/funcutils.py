from pymongo import MongoClient


def monogo_connector():
    client = MongoClient('mongodb://127.0.0.1:27017/')
    db = client.empresa
    col = db.funcionarios
    return col


def profile_finder(col, data):
    profileDoc = col.find({'ID': data[1:-1]})
    profileDoc = list(profileDoc)[0]
    return profileDoc


def profile_filter(profileDoc):
    keys = ['name', 'job']
    str_profile = {key: profileDoc[key] for key in keys}
    return str_profile