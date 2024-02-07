This folder contains research resources used in a paper published in SERA23

- Commit message can help: security patch detection in open source software via transformer. In 2023 IEEE/ACIS 21st International Conference on Software Engineering Research, Management and Applications (SERA) (pp. 345-351). IEEE.

*Please note the code is completed in Keras 2.*

1. Source code that is used to train a transformer-based model: commit_message_mining
2. A pre-trained model: model_49-accuracy0.92
3. sec_patch_commit_dict: dataset containing positive samples
4. non_patch_commit_dict: dataset containing negative samples
5. patch_commit_voc50_mc5: word2vec that is used to initialize word embeddings (d=50)
6. patch_commit_voc100_mc5: word2vec that is used to initialize word embeddings (d=100)
