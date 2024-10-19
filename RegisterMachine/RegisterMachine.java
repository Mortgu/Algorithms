import java.io.*;
import java.util.*;

class RegisterMachine {

    // Beinhaltet die Register als String und ihren Wert als Integer
    private Map<String, Integer> registers = new HashMap<>();    

    private List<String> instructions = new ArrayList<>();

    public RegisterMachine() {
        // Initalisiert den Accumulator mit 0.
        registers.put("Accumulator", 0);

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
        File programFile = new File(file);
        if (!programFile.exists() || !programFile.canRead()) {
            throw new IOException("File not found or cannot be read: " + file);
        }
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

            if (parts.length < 2 && !instruction.equals("END")) {
                System.out.println("Error: Invalid instruction format at line " + (pc + 1));
                return;
            }
        
            switch (instruction) {
                case "PRINT":
                    System.out.println(parts[1] + ": " + readRegister(parts[1]));
                    pc++;
                    break;
                case "CLR": 
                    setRegister(parts[1], 0);
                    pc++;           
                    break;
                case "LOAD", "CPY":
                    setRegister("Accumulator", readRegister(parts[1]));
                    pc++;
                    break;
                case "STORE":
                    setRegister(parts[1], readRegister("Accumulator"));
                    pc++;
                    break;
                case "ADD":
                    setRegister("Accumulator", readRegister("Accumulator") + readRegister(parts[1]));
                    pc++;
                    break;            
                case "SUB":
                    setRegister("Accumulator", readRegister("Accumulator") - readRegister(parts[1]));
                    pc++;
                    break;
                case "MUL":
                    setRegister("Accumulator", readRegister("Accumulator") * readRegister(parts[1]));
                    pc++;
                    break;
                case "DIV":
                    int divisor = readRegister(parts[1]);
                    if (divisor == 0) {
                        System.out.println("Error: Division by zero");
                        return;
                    }
                    setRegister("Accumulator", readRegister("Accumulator") / divisor);
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
                    if (readRegister("Accumulator") == 0)
                        pc = Integer.parseInt(parts[1]) - 1; 
                    else pc++;
                    break;
                case "JNZERO":
                    if (readRegister("Accumulator") != 0) 
                        pc = Integer.parseInt(parts[1]) - 1;
                    else pc++;
                    break;
                case "JUMP": 
                    pc = Integer.parseInt(parts[1]) - 1;
                    break; 
                case "END":
                    System.out.print("Accumulator: " + readRegister("Accumulator")); 
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
