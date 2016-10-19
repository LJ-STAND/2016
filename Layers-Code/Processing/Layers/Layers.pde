import processing.serial.*;
import java.util.List;

class Slider {
    public int x;
    public int y;
    public int w;
    public final int h = 10;
    private int sliderX;
    private final int sliderY;
    private float percent;
    public final int sliderW = 10;
    public final int sliderH = 20;
    public boolean clicked;
    public final String value;
    public final String display;

    public Slider(int x, int y, int w, String value, String display) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.sliderY = y - ((sliderH - 10) / 2);
        this.value = value;
        this.display = display;

        setPercent(50.0);
    }

    public void draw() {
        fill(38, 38, 38);
        stroke(38, 38, 38);

        rect(x, y, w, h);

        fill(89, 89, 89);
        stroke(89, 89, 89);

        rect(sliderX, sliderY, sliderW, sliderH);

        fill(0);
        stroke(0);
        textFont(avenir20);

        textAlign(LEFT);
        text(display, x, y - 15);
    }

    public void setSliderX(int x) {
        sliderX = constrain(x, this.x, (this.x + w - sliderW));
        percent = ((float)(sliderX - this.x) / (float)(w - sliderW)) * 100;
    }

    public int getSliderX() {
        return sliderX;
    }

    public void setPercent(float percent) {
        this.percent = constrain(percent, 0.0, 100.0);
        sliderX = (int)((percent / 100) * (w - sliderW)) + x + (int)((float)sliderW / 2);
    }

    public float getPercent() {
        return percent;
    }
}

class Button {
    public int x;
    public int y;
    public int w;
    public int h;
    public String value;

    public boolean hover;
    public boolean clicked = false;

    public Button(int x, int y, int w, int h, String value) {
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
        this.value = value;
    }

    public void draw() {
        strokeWeight(0);
        fill(clicked ? 13 : (hover ? 128 : 77));
        stroke(clicked ? 13 : (hover ? 128 : 77));

        rect(x, y, w, h, 3);

        fill(255);
        stroke(255);
        textFont(avenir20);
        textAlign(CENTER);

        text(value, x, y + 10, w, h - 14);
    }
}

class TextfieldString {
    public String value;
    public int type;

    public TextfieldString(String value, int type) {
        this.value = value;
        this.type = type;
    }
}

Serial port;

List<TextfieldString> consoleText = new ArrayList<TextfieldString>();
List<Button> buttons = new ArrayList<Button>();
List<Slider> sliders = new ArrayList<Slider>();

int scroll;
final int maxLines = 24;

float heading;
int tsopNum;

int motorLeftPower;
int motorRightPower;
int motorBackPower;

boolean isSelectionMenu = true;

PFont avenir20;
PFont avenir50;

int lastWidth;
int lastHeight;

void setup() {
    size(1280, 720);
    surface.setResizable(true);
    pixelDensity(displayDensity());
    
    lastWidth = width;
    lastHeight = height;

    avenir20 = loadFont("Avenir-Medium-20.vlw");
    avenir50 = loadFont("Avenir-Medium-50.vlw");

    setupMenu();
}

void setupMenu() {
    String ports[] = Serial.list();

    buttons.clear();

    for (int i = 0; i < ports.length; i++) {
        buttons.add(new Button((int)(((float) width - 780.0f) / 2) + 50, (int)(((float) height - 520.f) / 2) + 80 + (i * 60), 680, 40, ports[i]));
    }
}

void setupMain() {
     sliders.clear();

     sliders.add(new Slider(820, 300, 440, "power", "Power"));

     buttons.clear();

     buttons.add(new Button(820, 660, 80, 40, "Close"));
     buttons.add(new Button(920, 660, 80, 40, "Clear"));
     
     buttons.add(new Button(820, 470, 250, 40, "Calibrate Compass"));

     consoleText.clear();

     heading = 0;
     tsopNum = 0;
}

void draw() {
    if (width != lastWidth && height != lastHeight) {
        if (isSelectionMenu) {
            for (int i = 0; i < buttons.size(); i++) {
                Button button = buttons.get(i);
                
                button.x = (int)(((float) width - 780.0f) / 2) + 50;
                button.y = (int)(((float) height - 520.f) / 2) + 80 + (i * 60);
            }
        }
    }
    
    lastWidth = width;
    lastHeight = height;
    
    if (isSelectionMenu) {
        background(217, 217, 217);

        fill(255);
        stroke(255);
        strokeWeight(0);
        rect((int)(((float) width - 780.0f) / 2), (int)(((float) height - 520.f) / 2), 780, 520, 5);

        textFont(avenir50);
        textAlign(CENTER);
        fill(0);
        stroke(0);

        text("Ports", (int)(((float) width - 780.0f) / 2), (int)(((float) height - 520.f) / 2) + 20, 780, 100);
    } else {
        serialData();

        background(217, 217, 217);

        fill(255);
        stroke(255);
        strokeWeight(0);

        rect(0, 0, 800, 720);

        textAlign(LEFT);

        if (consoleText.size() > maxLines) {
            for (int i = scroll; i < scroll + maxLines; i++) {
                String displayText = consoleText.get(i).value;

                textFont(avenir20);

                if (consoleText.get(i).type == 1) {
                    fill(0, 51, 204);
                } else {
                    fill(0);
                }

                text(displayText, 10, 25 + (29.5 * (i - scroll)));
            }

            fill(128, 128, 128);
            stroke(128, 128, 128);

            rect(780, 0, 20, 720);

            fill(64, 64, 64);
            stroke(64, 64, 64);

            int barHeight = constrain((int)(((float) maxLines / (float) consoleText.size()) * 720), 10, 720);
            int barY = (int)(((float)scroll / (float)(consoleText.size() - maxLines)) * (720 - barHeight));

            rect(780, barY, 20, barHeight);
        } else {
            for (int i = 0; i < consoleText.size(); i++) {
                String displayText = consoleText.get(i).value;

                textFont(avenir20);

                if (consoleText.get(i).type == 1) {
                    fill(0, 51, 204);
                } else {
                    fill(0);
                }

                text(displayText, 10, 25 + (29.5 * i));
            }
        }

        fill(38, 38, 38);
        stroke(38, 38, 38);
        ellipse(1160, 120, 200, 200);

        fill(255);
        stroke(255);

        float headingCirclePosition = map(360 - heading, 0, 360, 0, TWO_PI) - HALF_PI;

        strokeWeight(10);
        line(1160, 120, (int)(1160 + cos(headingCirclePosition) * 85), (int)(120 + sin(headingCirclePosition) * 85));

        strokeWeight(0);

        for (int i = 0; i < 12; i++) {
            float circlePosition = map(i, 0, 12, 0, TWO_PI) - HALF_PI;

            if (i == tsopNum) {
                fill(0, 204, 102);
                stroke(0, 204, 102);
            } else {
                fill(0, 0, 0);
                stroke(0, 0, 0);
            }

            ellipse((int)(920 + cos(circlePosition) * 80), (int)(120 + sin(circlePosition) * 80), 20, 20);
        }

        for (Slider slider : sliders) {
            slider.draw(); 
        }
        
        fill(89, 89, 89);
        stroke(89, 89, 89);
        
        rect(820, 360, 440, 20);
        rect(820, 390, 440, 20);
        rect(820, 420, 440, 20);
        
        fill(38, 38, 38);
        stroke(38, 38, 38);
        
        rect(820, 360, (int)(((float)motorLeftPower / 255.0) * 440), 20);
        rect(820, 390, (int)(((float)motorRightPower / 255.0) * 440), 20);
        rect(820, 420, (int)(((float)motorBackPower / 255.0) * 440), 20);
    }

    boolean isOnButton = false;

    for (Button button : buttons) {
        if (mouseX > button.x && mouseX < button.x + button.w && mouseY > button.y && mouseY < button.y + button.h) {
            button.hover = true;
            isOnButton = true;
        } else {
            button.hover = false;
        }

        button.draw();
    }

    cursor(isOnButton ? HAND : ARROW);
}

void serialData() {
    int newLine = 13;
    String message;
    do {
        message = port.readStringUntil(newLine);
        if (message != null) {
            String[] list = split(trim(message), ";");

            if (list.length == 2) {
                if (list[0].equals("2")) {
                    heading = float(list[1]);
                } else if (list[0].equals("1")) {
                    display(list[1], 0);
                } else if (list[0].equals("0")) {
                    tsopNum = int(list[1]);
                } else if (list[0].equals("3")) {
                    motorLeftPower = int(list[1]);
                } else if (list[0].equals("4")) {
                    motorRightPower = int(list[1]);
                } else if (list[0].equals("5")) {
                    motorBackPower = int(list[1]);
                }
            }
        }
    } while (message != null);
}

void send(int data, int dataCode) {
    String sendString = dataCode + ";" + data;
    port.write(dataCode + ";" + data);
    display(sendString, 1);
}

void display(String text, int type) {
    consoleText.add(new TextfieldString(text, type));
    scrollToBottom();
}

void clearConsole() {
    consoleText.clear();
}

void mouseWheel(MouseEvent event) {
    int e = (int) event.getCount();
    if ((consoleText.size() > maxLines && scroll < consoleText.size() - maxLines && e > 0) || (consoleText.size() > maxLines && scroll > 0 && e < 0)) {
       scroll += e;
    }

    if (scroll < 0) {
        scroll = 0;
    }

    if (scroll > consoleText.size() - maxLines) {
        scroll = consoleText.size() - maxLines;
    }
}

void scrollToBottom() {
    if (scroll < consoleText.size() - maxLines) {
        scroll = consoleText.size() - maxLines;
    }

    if (scroll < 0) {
        scroll = 0;
    }
}

void mousePressed(MouseEvent event) {
    for (Button button : buttons) {
        if (event.getX() > button.x && event.getX() < button.x + button.w && event.getY() > button.y && event.getY() < button.y + button.h) {
            button.clicked = true;
        } else {
            button.clicked = false;
        }

        button.draw();
    }

    for (Slider slider : sliders) {
        if (event.getX() > slider.getSliderX() && event.getX() < slider.getSliderX() + slider.sliderW && event.getY() > slider.sliderY && event.getY() < slider.sliderY + slider.sliderH) {
            slider.clicked = true;
        } else if (event.getX() > slider.x && event.getX() < slider.x + slider.w && event.getY() > slider.y && event.getY() < slider.y + slider.h) {
            slider.setSliderX((int)(event.getX() - (int)((float)slider.sliderW / 2)));
            slider.clicked = true;

            if (slider.value == "power") {
                send((int)((slider.percent / 100) * 255), 0);
            }
        }
    }
}


void mouseDragged(MouseEvent event) {
    for (Button button : buttons) {
        if (event.getX() > button.x && event.getX() < button.x + button.w && event.getY() > button.y && event.getY() < button.y + button.h) {
            button.clicked = true;
        } else {
            button.clicked = false;
        }

        button.draw();
    }

    for (Slider slider : sliders) {
        if (slider.clicked) {
            slider.setSliderX((int)(event.getX() - (int)((float)slider.sliderW / 2)));

            if (slider.value == "power") {
                send((int)((slider.percent / 100) * 255), 0);
            }
        }
    }
}

void mouseReleased(MouseEvent event) {
    if (isSelectionMenu) {
        boolean hasClicked = false;

        for (Button button : buttons) {
            if (event.getX() > button.x && event.getX() < button.x + button.w && event.getY() > button.y && event.getY() < button.y + button.h && button.clicked) {
                try {
                    port = new Serial(this, button.value, 9600);
                    isSelectionMenu = false;
                    hasClicked = true;
                    break;
                } catch (RuntimeException e) {
                    button.clicked = false;
                    button.draw();
                }
            }
        }

        if (hasClicked) {
            setupMain();
        }
    } else {
        boolean hasClickedClose = false;

        for (Button button : buttons) {
            if (event.getX() > button.x && event.getX() < button.x + button.w && event.getY() > button.y && event.getY() < button.y + button.h && button.clicked) {
                if (button.value == "Close") {
                    hasClickedClose = true;
                    isSelectionMenu = true;
                } else if (button.value == "Clear") {
                    clearConsole();
                    scroll = 0;
                } else if (button.value == "Calibrate Compass") {
                    send(0, 8);
                }

                button.clicked = false;
            }
        }

        if (hasClickedClose) {
            port.stop();
            port = null;
            setupMenu();
        }
    }

    for (Slider slider : sliders) {
        slider.clicked = false;
    }
}