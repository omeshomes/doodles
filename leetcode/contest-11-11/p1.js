var pivotIndex = function(nums) {
    var length = nums.length;
    var totalSum = nums.reduce(function(a, b) {return a+b});
    var leftSum = 0;
    var rightSum = totalSum - nums[0];
    // console.log(totalSum);
    if (length === 1) {
        return 0;
    } else if (totalSum - nums[0] === 0) {
        return 1;
    } else if (totallsSum - nums[length-1] === 0) {
        return length - 1;
    }
    for (var i = 1; i < length - 1; i++) {
        leftSum += nums[i-1];
        rightSum -= nums[i];
        // console.log(i, leftSum, rightSum);
        if (leftSum === rightSum) {
            return i;
        }
    }
    return -1;
};

console.log(pivotIndex([1,2,3,4,6]));