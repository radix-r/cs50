import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # positives and negatives are paths to text files
        # open  
        posFile = open(positives, "r")# do i need to close it?
        # list of positive words
        self.posWords = []
        
        # read from file 
        for line in posFile:
            #ignore comments
            if line[0].isalpha():
                self.posWords.append(line.rstrip("\n"))

        posFile.close()

        # now for the negative words
        negFile = open(negatives, "r")
        self.negWords = []
        
        for line in negFile:
            if line[0].isalpha():
                self.negWords.append(line.rstrip("\n"))
                
        negFile.close()
    
       
       
       
    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        # tokenize the tweet
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        
        value = 0
        for token in tokens:
            if token.lower() in self.posWords:
                value = value + 1
            elif token.lower() in self.negWords:
                value = value - 1
        
        return value
        