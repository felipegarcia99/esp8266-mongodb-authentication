#Código separado em funções, seguindo a boa prática de organização do código
from wificonnection import TCPsocket
from funcutils import monogo_connector, profile_filter, profile_finder

def main():
    #Iniciando conexão com o mongoDB
    col = monogo_connector()

    #Iniciando servidor TCPSocket
    ws = TCPsocket()
    while True:
        #Recebendo ID do cartão vindo do esp8266
        data = ws.receber_dado_tratado()
        if not data:
            continue
        print('data: ', data)

        #Encontrando o perfil no mongoDB baseado na chave ID
        profileDoc = profile_finder(col, data)
        print('perfil encontrado: ', profileDoc)

        #Filtrando apenas os valores essenciais para enviar ao esp8266
        str_profile = profile_filter(profileDoc)
        print('perfil filtrado: ', str_profile)

        #Enviando JSON do perfil para o esp8266 (na forma de string)
        ws.enviar(str(str_profile))
        print('**************************')


if __name__ == '__main__':
    main()