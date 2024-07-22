APP = testapp

# Add any other object files to this list below
SRC = i2c.c spi.c uart.c ddr.c ethernet.c registers.c can_registers.c AFDX_registers.c core_configuration.c crc_core.c testapp.c  
APP_OBJS = $(SRC:.c=.o)
#APP_OBJS = testapp.o

all: build

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) -o $@ $(APP_OBJS) $(LDFLAGS) $(LDLIBS)
clean:
	rm -f $(APP) *.o
