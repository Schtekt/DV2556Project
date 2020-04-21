pipeline{
    agent any

    stages{
        stage ('Build') {
            steps{
                sh 'echo "Building..."'
                sh 'chmod +x Scripts/linux-build.sh'
                sh 'Scripts/linux-build.sh'
                archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
            }
        }

        stage ('Test') {
            steps{
                sh 'echo "Running..."'
                sh 'chmod +x Scripts/linux-run.sh'
                sh 'Scripts/linux-run.sh'
            }
        }
    }
}