import socket

class TCPsocket():
	def __init__(self):
		host = socket.gethostname()   # get local machine name
		print('Host:', host)
		port = 8080  # Make sure it's within the > 1024 $$ <65535 range

		self.s = socket.socket()
		self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)	
		self.s.bind(('', port))
	  	
		self.s.listen(1)
		print('Listening...')
	  
		self.client_socket, self.adress = self.s.accept()
		print("Connection from: " + str(self.adress))
		print('client_socket:', self.client_socket)

	def reconectar(self):
		self.s.listen(1)
		print('Listening...')
	  
		self.client_socket, self.adress = self.s.accept()
		print("Connection from: " + str(self.adress))
		print('client_socket:', self.client_socket)

	def receber(self):
		data = self.client_socket.recv(1024).decode('utf-8')

		return data
	
	def receber_dado_tratado(self):
		data = self.receber()
		if not data:
			print('dado inválido, o cliente desconectou, saindo...')
			self.reconectar()
			return False
			
		if data == '\r\n':
			return False
			
		return data

	def enviar(self, data):
		self.client_socket.send(data.encode('utf-8'))

	def __del__(self):
		print('Closing connection')
		self.client_socket.close()
