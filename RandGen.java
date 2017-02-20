
    public static void main(String[] args) {
        Random r = new Random();
        int max = Short.MAX_VALUE;
        int min = Short.MIN_VALUE;
        int del = max - min;
        int count = 10;
        int pow = 5; //maximum power of 10
        for(int i = 1; i <= pow; i++) {
            count *= 10;
            int[] nums = new int[count];
            int start = -(count / 2);
            for(int j = 0; j < count; j++) {
                nums[j] = start++;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_increasing");
            for(int j = 0; j < count; j++) {
                nums[j] = start--;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_decreasing");
            for(int j = 0; j < count; j++) {
                int dest = r.nextInt(count);
                int temp = nums[dest];
                nums[dest] = nums[j];
                nums[j] = temp;
            }
            out(count, (int j)->{return nums[j];}, "in_" + i + "_random");
        }
    }