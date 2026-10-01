# Configurações da placa
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyACM0
BAUD = 115200

# Ferramentas
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# Flags de compilação
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall

# Busca todos os arquivos .c no projeto (inclusive subpastas)
SRC = $(shell find . -name '*.c')
OBJ = $(SRC:.c=.o)

# Arquivos de saída
TARGET = main
ELF = $(TARGET).elf
HEX = $(TARGET).hex

# Regras
all: $(HEX)

$(ELF): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(HEX)
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(HEX)

clean:
	rm -f $(ELF) $(HEX) $(OBJ)
