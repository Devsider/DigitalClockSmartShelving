void digitZero(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 12);
    stripClock.fill(colour, (16 + offset), 12);
}

void digitOne(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 4);
    stripClock.fill(colour, (16 + offset), 4);
}

void digitTwo(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 8);
    stripClock.fill(colour, (12 + offset), 4);
    stripClock.fill(colour, (20+ offset), 8);
}

void digitThree(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 8);
    stripClock.fill(colour, (12 + offset), 12);
}

void digitFour(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 4);
    stripClock.fill(colour, (8 + offset), 12);
}

void digitFive(int offset, int colour){
    stripClock.fill(colour, (4 + offset), 20);
}

void digitSix(int offset, int colour){
    stripClock.fill(colour, (4 + offset), 24);
}

void digitSeven(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 8);
    stripClock.fill(colour, (16 + offset), 4);
}

void digitEight(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 28);
}

void digitNine(int offset, int colour){
    stripClock.fill(colour, (0 + offset), 20);
}