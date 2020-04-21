pipeline{
    agent any

    stages{
        stage ('Build') {
            steps{
                sh 'echo "Building..."'
                sh 'Scripts/linux-build.sh'
                archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
            }
        }

        stage ('Test') {
            steps{
                sh 'echo "Running..."'
                sh 'Scripts/linux-run.sh'
            }
        }
    }
}