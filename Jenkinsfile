pipeline{
    agent any

    stages{
        stage ('Build') {
            steps{
                sh 'echo "Building..."'
                sh 'sudo chmod +x Scripts/linux-build.sh'
                sh 'sudo Scripts/linux-build.sh'
                archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
            }
        }

        stage ('Test') {
            steps{
                sh 'echo "Running..."'
                sh 'sudo chmod +x Scripts/linux-run.sh'
                sh 'sudo Scripts/linux-run.sh'
            }
        }
    }
}