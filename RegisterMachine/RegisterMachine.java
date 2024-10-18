import java.io.*;
import java.util.*;

class RegisterMachine {

    // Beinhaltet die Register als String und ihren Wert als Integer
    private Map<String, Integer> registers = new HashMap<>();    

    private List<String> instructions = new ArrayList<>();

    public RegisterMachine() {
        // Initalisiert den akkumulator mit 0.
        registers.put("Akkumulator", 0);

        // Initialisiere die Register R1 - R4 mit dem Wert 0
        for (int i = 1; i <= 4; i++) {
            registers.put("R" + i, 0);
        }
    }

    // Ändert den Wert eines Registers oder erstellt ein neues register.
    private void setRegister(String register, int value) {
        registers.put(register, value);
    }

    // Retured den aktuellen Wert des Registers
    private int readRegister(String register) {
        return registers.getOrDefault(register, 0);
    }

    public void loadProgram(String file) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line;

        while ((line = reader.readLine()) != null) {
            if (line.length() <= 0 || line.startsWith("//")) {
                continue;
            }
            instructions.add(line.trim());
        }

        reader.close();
    }

    public void run() {
        int pc = 0;

        while (pc < instructions.size()) {
            String line = instructions.get(pc);            
            String[] parts = line.split(" ");
            String instruction = parts[0];

            System.out.println("pc: " + pc);
        
            switch (instruction) {
                case "PRINT":
                    System.out.println(parts[1] + ": " + readRegister(parts[1]));
                    pc++;
                    break;
                case "CLR": 
                    setRegister(parts[1], 0);
                    pc++;           
                    break;
                case "LOAD":
                    setRegister("Akkumulator", readRegister(parts[1]));
                    pc++;
                    break;
                case "STORE":
                    setRegister(parts[1], readRegister("Akkumulator"));
                    pc++;
                    break;
                case "CPY":
                    setRegister("Akkumulator", readRegister(parts[1]));
                    pc++;
                    break;
                case "ADD":
                    setRegister("Akkumulator", readRegister("Akkumulator") + readRegister(parts[1]));
                    pc++;
                    break;            
                case "SUB":
                    setRegister("Akkumulator", readRegister("Akkumulator") - readRegister(parts[1]));
                    pc++;
                    break;
                case "MUL":
                    setRegister("Akkumulator", readRegister("Akkumulator") * readRegister(parts[1]));
                    pc++;
                    break;
                case "DIV":
                    setRegister("Akkumulator", readRegister("Akkumulator") / readRegister(parts[1]));
                    pc++;
                    break;
                case "INC":
                    setRegister(parts[1], readRegister(parts[1]) + 1);
                    pc++;
                    break;
                case "DEC":
                    setRegister(parts[1], readRegister(parts[1]) - 1);
                    pc++;
                    break;
                case "JZERO": 
                    if (readRegister("Akkumulator") == 0)
                        pc = Integer.parseInt(parts[1]) - 1; 
                    else pc++;
                    break;
                case "JNZERO":
                    if (readRegister("Akkumulator") != 0) 
                        pc = Integer.parseInt(parts[1]) - 1;
                    else pc++;
                    break;
                case "JUMP": 
                    pc = Integer.parseInt(parts[1]) - 1;
                    break; 
                case "END":
                    System.out.print("Akkumulator: " + readRegister("Akkumulator")); 
                    System.out.print(" R1: " + readRegister("R1")); 
                    System.out.print(" R2: " + readRegister("R2")); 
                    System.out.print(" R3: " + readRegister("R3")); 
                    System.out.print(" R4: " + readRegister("R4"));
                    System.out.println(" ");
                    return;
                default:
                    pc++;
                    System.out.println("Instruction: " + instruction + " not found!");
                    break;
            }
        }
    }

    public static void main(String[] args) {
        if (args.length <= 0) {
            System.out.println("Missing file!");
            return;
        } 

        String file = args[0];
        RegisterMachine registerMachine = new RegisterMachine();

        try {
            registerMachine.loadProgram(file);
        } catch (IOException exception) {
            exception.printStackTrace();
        }
        registerMachine.run();
    }
}
