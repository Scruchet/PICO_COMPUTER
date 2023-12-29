DIRS=Ordonnanceur Tests/Mem Tests/7seg Tests/Mat_leds Tests/UART_SPI #EDR

clean: $(patsubst %, _clean_%, $(DIRS))

$(patsubst %,_clean_%,$(DIRS)):
	cd $(patsubst _clean_%,%,$@) && make clean


format: $(patsubst %, _format_%, $(DIRS))

$(patsubst %,_format_%,$(DIRS)):
	cd $(patsubst _format_%,%,$@) && make format
