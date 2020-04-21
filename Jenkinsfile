pipeline{
    agent any

    stages{
        stage ('Build') {
            steps{
                sh 'echo "Building..."'
                sh 'sudo chmod +x scripts/linux-build.sh'
                sh 'sudo scripts/linux-build.sh'
                archiveArtifacts artifacts: 'bin/Debug/*', fingerprint: true
            }
        }

        stage ('Test') {
            steps{
                sh 'echo "Running..."'
                sh 'sudo chmod +x scripts/linux-run.sh'
                sh 'sudo scripts/linux-run.sh'
            }
        }
    }
}