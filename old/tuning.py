print("D4 Thames Tuning System")

class PID:
	p = 0
	i = 0
	d = 0
	I = 0

pitch = PID()
roll = PID()
yaw = PID()

data_in_buffer = False

while True:
	user_input = input("> ").split(" ")
	if user_input[0].lower() == "pitch":
		user_input = user_input[1:]
		for i in range(len(user_input)):
			try:
				if user_input[i][0] == 'p':
					pitch.p = float(user_input[i][1:])
					data_in_buffer = True
					print("Set pitch's proportional coefficient to %f" % pitch.p)
				if user_input[i][0] == 'i':
					pitch.i = float(user_input[i][1:])
					data_in_buffer = True
					print("Set pitch's integral coefficient to %f" % pitch.i)
				if user_input[i][0] == 'I':
					pitch.I = float(user_input[i][1:])
					data_in_buffer = True
					print("Set pitch's integral threshold to %f" % pitch.I)
				if user_input[i][0] == 'd':
					pitch.d = float(user_input[i][1:])
					data_in_buffer = True
					print("Set pitch's differential coefficient to %f" % pitch.d)					
			except:
				print("Invalid Input!")
	elif user_input[0].lower() == "roll":
		user_input = user_input[1:]
		for i in range(len(user_input)):
			try:
				if user_input[i][0] == 'p':
					roll.p = float(user_input[i][1:])
					data_in_buffer = True
					print("Set roll's proportional coefficient to %f" % roll.p)
				if user_input[i][0] == 'i':
					roll.i = float(user_input[i][1:])
					data_in_buffer = True
					print("Set roll's integral coefficient to %f" % roll.i)
				if user_input[i][0] == 'I':
					roll.I = float(user_input[i][1:])
					data_in_buffer = True
					print("Set roll's integral threshold to %f" % roll.I)
				if user_input[i][0] == 'd':
					roll.d = float(user_input[i][1:])
					data_in_buffer = True
					print("Set roll's differential coefficient to %f" % roll.d)
			except:
				print("Invalid Input!")
	elif user_input[0].lower() == "yaw":
		user_input = user_input[1:]
		for i in range(len(user_input)):
			try:
				if user_input[i][0] == 'p':
					yaw.p = float(user_input[i][1:])
					data_in_buffer = True
					print("Set yaw's proportional coefficient to %f" % yaw.p)
				if user_input[i][0] == 'i':
					yaw.i = float(user_input[i][1:])
					data_in_buffer = True
					print("Set yaw's integral coefficient to %f" % yaw.i)
				if user_input[i][0] == 'I':
					yaw.I = float(user_input[i][1:])
					data_in_buffer = True
					print("Set yaw's integral threshold to %f" % yaw.I)
				if user_input[i][0] == 'd':
					yaw.d = float(user_input[i][1:])
					data_in_buffer = True
					print("Set yaw's differential coefficient to %f" % yaw.d)
			except:
				print("Invalid Input!")
	elif user_input[0].lower() == "send" or user_input[0].lower() == "update":
		print("Sending Data...")
		#TODO Send the Data.
		print("Done")
		data_in_buffer = False
	elif user_input[0].lower() == "status":
		if (data_in_buffer):
			print("Data yet to be sent.")
		else:
			print("Up-to-date with drone.")
		print("pitch p%f i%f d%f I%f" % (pitch.p, pitch.i, pitch.d, pitch.I))
		print("roll  p%f i%f d%f I%f" % (roll.p, roll.i, roll.d, roll.I))
		print("yaw   p%f i%f d%f I%f" % (yaw.p, yaw.i, yaw.d, yaw.I))