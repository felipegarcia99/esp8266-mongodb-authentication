# Código por extenso; sem funções
from wificonnection import TCPsocket
from pymongo import MongoClient


def main():
    #Iniciando conexão com o mongoDB
    client = MongoClient('mongodb://127.0.0.1:27017/')
    db = client.empresa
    col = db.funcionarios

    #Iniciando servidor TCPSocket
    ws = TCPsocket()
    while True:
        #Recebendo ID do cartão vindo do esp8266
        data = ws.receber()
        if not data:
            print('dado inválido, o cliente desconectou, saindo...')
            ws.reconectar()
            continue
        
        if data == '\r\n':
            continue
        
        print('data: ', data)

        #Encontrando o perfil no mongoDB baseado na chave ID
        profileDoc = col.find({'ID': data[1:-1]})
        profileDoc = list(profileDoc)[0]
        print('perfil encontrado: ', profileDoc)

        #Filtrando apenas os valores essenciais para enviar ao esp8266
        keys = ['name', 'job']
        str_profile = {key: profileDoc[key] for key in keys}
        print('perfil filtrado: ', str_profile)

        #Enviando JSON do perfil para o esp8266 (na forma de string)
        ws.enviar(str(str_profile))
        print('**************************')


if __name__ == '__main__':
    main()