import pymongo
from faker import Faker

faker = Faker('pt-BR')

client = pymongo.MongoClient('mongodb://127.0.0.1:27017/')
db = client.empresa
col = db.funcionarios

ids = ['17 16 52 D3',
        'C6 B5 BD 1A',
        'D6 29 6A 1A']

for i in range(len(ids)):
    humano = faker.profile()
    humano['ID'] =  ids[i]
    # Removendo itens que dão problema com o mongodb
    # (Até porque isso é só um exemplo, não precisa de muito)
    del humano['current_location']
    del humano['birthdate']
    print(humano)
    col.insert(humano)
